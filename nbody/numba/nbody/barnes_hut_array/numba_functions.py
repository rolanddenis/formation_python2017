import numpy as np
import numba
from ..forces import force
from ..physics import gamma_si

@numba.njit
def buildTree(center0, box_size0, child, cell_center, cell_radius, particles):
    ncell = 0
    nbodies = particles.shape[0]
    for ip in range(nbodies):
        center = center0.copy()
        box_size = box_size0
        x, y = particles[ip, :2]
        cell = 0

        childPath = 0
        if x > center[0]:
            childPath += 1
        if y > center[1]:
            childPath += 2

        childIndex = nbodies + childPath

        while (child[childIndex] > nbodies):
            cell = child[childIndex] - nbodies
            center[:] = cell_center[cell]
            childPath = 0
            if x > center[0]:
                childPath += 1
            if y > center[1]:
                childPath += 2
            childIndex = nbodies + 4*cell + childPath
        # no particle on this cell, just add it
        if (child[childIndex] == -1):
            child[childIndex] = ip
            child[ip] = cell
        # this cell already has a particle
        # subdivide and set the two particles
        elif (child[childIndex] < nbodies):
            npart = child[childIndex]

            oldchildPath = newchildPath = childPath
            while (oldchildPath == newchildPath):
                ncell += 1
                child[childIndex] = nbodies + ncell
                center[:] = cell_center[cell]
                box_size = .5*cell_radius[cell]
                if (oldchildPath&1):
                    center[0] += box_size
                else:
                    center[0] -= box_size
                if ((oldchildPath>>1)&1):
                    center[1] += box_size
                else:
                    center[1] -= box_size

                oldchildPath = 0
                if particles[npart, 0] > center[0]:
                    oldchildPath += 1
                if particles[npart, 1] > center[1]:
                    oldchildPath += 2

                newchildPath = 0
                if particles[ip, 0] > center[0]:
                    newchildPath += 1
                if particles[ip, 1] > center[1]:
                    newchildPath += 2

                cell = ncell

                cell_center[ncell] = center
                cell_radius[ncell] = box_size

                childIndex = nbodies + 4*ncell + oldchildPath

            child[childIndex] = npart
            child[npart] = ncell

            childIndex = nbodies + 4*ncell + newchildPath
            child[childIndex] = ip
            child[ip] = ncell
    return ncell


@numba.njit
def sortTree(nbodies, child_array, cell_center, cell_radius):
    old_child_array = child_array.copy()
    old_cell_center = cell_center.copy()
    old_cell_radius = cell_radius.copy()

    depth = 0
    localPos = np.zeros(2*nbodies, dtype=np.int32)
    localChild = np.zeros(2*nbodies, dtype=np.int32)
    localChild[0] = nbodies

    old_localChild = localChild.copy()

    ncell = 1

    while depth >= 0:
        while localPos[depth] < 4:
            pos = nbodies + 4*(localChild[depth]-nbodies) + localPos[depth]
            old_pos = nbodies + 4*(old_localChild[depth]-nbodies) + localPos[depth]

            localPos[depth] += 1
            old_child = old_child_array[old_pos]

            if old_child >= nbodies: # a cell
                child = ncell + nbodies
                ncell += 1
                child_array[pos] = child
                cell_radius[child-nbodies, 0] = old_cell_radius[old_child-nbodies, 0]
                cell_radius[child-nbodies, 1] = old_cell_radius[old_child-nbodies, 1]
                cell_center[child-nbodies, 0] = old_cell_center[old_child-nbodies, 0]
                cell_center[child-nbodies, 1] = old_cell_center[old_child-nbodies, 1]

                depth += 1
                localChild[depth] = child
                old_localChild[depth] = old_child
                localPos[depth] = 0
            elif old_child >= 0:     # a star
                child_array[pos] = old_child
                child_array[old_child] = localChild[depth]
            else:                    # nothing
                child_array[pos] = old_child

        depth -= 1

# @numba.njit
# def computeForce(nbodies, child_array, center_of_mass, mass, cell_radius, p):
#     depth = 0
#     localPos = np.zeros(2*nbodies, dtype=np.int32)
#     localNode = np.zeros(2*nbodies, dtype=np.int32)
#     localNode[0] = nbodies

#     pos = p[:2]
#     acc = np.zeros(2)

#     while depth >= 0:
#         while localPos[depth] < 4:
#             child = child_array[localNode[depth] + localPos[depth]]
#             # print('child 1', child, localNode[depth] + localPos[depth])
#             localPos[depth] += 1
#             if child >= 0:
#                 eps = 0.1*0.1 # approx. 3 light year
#                 dx = center_of_mass[child, 0] - pos[0]
#                 dy = center_of_mass[child, 1] - pos[1]
#                 if child < nbodies:
#                     #if child != ip:
#                         dist = np.sqrt(dx**2 + dy**2 + eps)
#                         if dist > 0:
#                             F = (gamma_si * mass[child]) / (dist*dist*dist)
#                         else:
#                             F = 0.
#                         acc += np.array([F * dx, F * dy])
#                 else:
#                     dist = np.sqrt(dx**2 + dy**2)
#                     #print(dist, localNode[depth], self.cell_radius[child - self.nbodies],
#                     # self.cell_radius[child - self.nbodies]/dist)
#                     if dist != 0 and cell_radius[child - nbodies]/dist <.5:
#                         #print('dist', dx, dy)
#                         F = gamma_si*mass[child]/(dist*dist*dist)
#                         acc += np.array([F * dx, F * dy])
#                     else:
#                         depth += 1
#                         localNode[depth] = nbodies + 4*(child-nbodies)
#                         localPos[depth] = 0
#         depth -= 1
#     return acc

@numba.njit
def computeForce(nbodies, child_array, center_of_mass, mass, cell_radius, p):
    depth = 0
    localPos = np.zeros(2*nbodies, dtype=np.int32)
    localNode = np.zeros(2*nbodies, dtype=np.int32)
    localNode[0] = nbodies

    pos = p[:2]
    acc = np.zeros(2)

    while depth >= 0:
        while localPos[depth] < 4:
            child = child_array[localNode[depth] + localPos[depth]]
            localPos[depth] += 1
            if child >= 0:
                if child < nbodies:
                    Fx, Fy = force(pos, center_of_mass[child], mass[child])
                    acc[0] += Fx
                    acc[1] += Fy
                else:
                    dx = center_of_mass[child, 0] - pos[0]
                    dy = center_of_mass[child, 1] - pos[1]
                    dist = np.sqrt(dx**2 + dy**2)
                    if dist != 0 and cell_radius[child - nbodies]/dist <.5:
                        Fx, Fy = force(pos, center_of_mass[child], mass[child])
                        acc[0] += Fx
                        acc[1] += Fy
                    else:
                        depth += 1
                        localNode[depth] = nbodies + 4*(child-nbodies)
                        localPos[depth] = 0
        depth -= 1
    return acc

@numba.njit
def computeMassDistribution(nbodies, ncell, child, mass, center_of_mass ):
    for i in range(ncell, -1, -1):
        this_mass = 0
        this_center_of_mass = [0, 0]
        for j in range( nbodies + 4*i, nbodies + 4*i + 4 ):
            element_id = child[j]
            if element_id >= 0:
                this_mass += mass[ element_id ]
                this_center_of_mass[0] += center_of_mass[element_id][0] * mass[element_id]
                this_center_of_mass[1] += center_of_mass[element_id][1] * mass[element_id]

        center_of_mass[nbodies + i][0] = this_center_of_mass[0] / this_mass
        center_of_mass[nbodies + i][1] = this_center_of_mass[1] / this_mass
        mass[nbodies + i] = this_mass

