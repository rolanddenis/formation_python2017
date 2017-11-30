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

#@numba.njit
def computeForce(nbodies, child_array, center_of_mass, mass, cell_radius, p, lhs_child):
    depth = 0
    localPos = np.zeros(2*nbodies, dtype=np.int32)
    localNode = np.zeros(2*nbodies, dtype=np.int32)
    localNode[0] = nbodies

    pos = p[:2]
    acc = np.zeros(2)

    stats = [0, 0]

    while depth >= 0:
        while localPos[depth] < 4:
            child = child_array[localNode[depth] + localPos[depth]]
            localPos[depth] += 1
            if child >= 0:
                if child < nbodies:
                    Fx, Fy = force(pos, center_of_mass[child], mass[child])
                    acc[0] += Fx
                    acc[1] += Fy
                    print('star2star (nbodies = {}, lhs_child = {}, rhs_child = {})'.format(nbodies, lhs_child, child))
                    stats[0] += 1
                else:
                    dx = center_of_mass[child, 0] - pos[0]
                    dy = center_of_mass[child, 1] - pos[1]
                    dist = np.sqrt(dx**2 + dy**2)
                    if dist != 0 and cell_radius[child - nbodies]/dist <.5:
                        Fx, Fy = force(pos, center_of_mass[child], mass[child])
                        acc[0] += Fx
                        acc[1] += Fy
                        print('star2cell (nbodies = {}, lhs_child = {}, rhs_child = {})'.format(nbodies, lhs_child, child))
                        stats[1] += 1
                    else:
                        depth += 1
                        localNode[depth] = nbodies + 4*(child-nbodies)
                        localPos[depth] = 0
        depth -= 1

    return acc, stats


def computeForce2(nbodies, child_array, center_of_mass, mass, cell_center, cell_radius, acc):
    
    print()
    print(child_array[0:nbodies])
    for i in range(nbodies, child_array[nbodies-1]+1):
        print('{}: {}', i, child_array[(nbodies + 4*(i-nbodies)):(nbodies + 4*(i-nbodies)+4)])

    #stats = {'star2star': 0, 'star2cell': 0, 'cell2star': 0, 'cell2cell': 0}
    stats = [0, 0, 0, 0]
    computeForce2_impl(nbodies, child_array, center_of_mass, mass, cell_center, cell_radius, acc, nbodies, child_array[nbodies-1]+1, nbodies, stats)
    # ncell instead of child_array[nbodies-1]+1 ?
    stats = {'star2star': stats[0], 'star2cell': stats[1], 'cell2star': stats[2], 'cell2cell': stats[3]}
    print(stats)

#@numba.njit
def computeForce2_impl(nbodies, child_array, center_of_mass, mass, cell_center, cell_radius, acc, lhs_child, lhs_end_child, rhs_child, stats):

    print("nbodies = {}, lhs_child = {}, lhs_end_child = {}, rhs_child = {}".format(nbodies, lhs_child, lhs_end_child, rhs_child))
    #print()

    ###########################################################################
    # If both childs are stars
    if lhs_child < nbodies and rhs_child < nbodies:
        if lhs_child != rhs_child:
            Fx, Fy = force(center_of_mass[lhs_child], center_of_mass[rhs_child], mass[rhs_child])
            acc[lhs_child, 0] += Fx
            acc[lhs_child, 1] += Fy
            
            #print('star2star')
            print('star2star (nbodies = {}, lhs_child = {}, rhs_child = {})'.format(nbodies, lhs_child,  rhs_child ))
            stats[0] += 1
        return

    ###########################################################################
    # If lhs child is a star and rhs child is a cell
    if lhs_child < nbodies:
        sqr_dist = ((center_of_mass[rhs_child, 0] - center_of_mass[lhs_child, 0])**2
                    + (center_of_mass[rhs_child, 1] - center_of_mass[rhs_child, 1])**2)

        # If theta is low, reduce the rhs cell to its center of mass
        if cell_radius[rhs_child - nbodies, 0]**2 < 0.25 * sqr_dist:
            Fx, Fy = force(center_of_mass[lhs_child], center_of_mass[rhs_child], mass[rhs_child])
            acc[lhs_child, 0] += Fx
            acc[lhs_child, 1] += Fy
            print('star2cell (nbodies = {}, lhs_child = {}, rhs_child = {})'.format(nbodies, lhs_child,  rhs_child ))
            stats[1] += 1
        # otherwise split the rhs cell.
        else:
            for i in range(4):
                new_child = child_array[nbodies + 4*(rhs_child - nbodies) + i]
                if new_child >= 0:
                    computeForce2_impl(nbodies, child_array, center_of_mass, mass, cell_center, cell_radius, acc, lhs_child, lhs_end_child, new_child, stats)

        return

    ###########################################################################
    # If lhs child is a cell and rhs child is a star,
    # calculate interaction of the rhs star with each star of the lhs cell.
    if rhs_child < nbodies:
        for i in range(nbodies + 4*(lhs_child - nbodies), nbodies + 4*(lhs_end_child - nbodies)):
            if 0 <= child_array[i] and child_array[i] < nbodies:
                Fx, Fy = force(center_of_mass[child_array[i]], center_of_mass[rhs_child], mass[rhs_child])
                acc[child_array[i], 0] += Fx
                acc[child_array[i], 1] += Fy
                print('cell2star ( nbodies = {}, lhs_child = {}, rhs_child = {})'.format(nbodies, child_array[i], rhs_child ))
                stats[2] += 1
        return

    ###########################################################################
    # If both childs are cells
    
    ###########################################################################
    # If both childs are same cell, we split both cells
    if lhs_child == rhs_child:
        # Calculating next child position
        array_pos = nbodies + 4*(lhs_child - nbodies)
        next_end_child = [lhs_end_child] * 4
        for i in range(2, -1, -1):
            if child_array[array_pos + i + 1] >= nbodies:
                next_end_child[i] = child_array[array_pos + i + 1]
            else:
                next_end_child[i] = next_end_child[i+1]
        
        # Iterating on lhs childs
        for i in range(4):
            new_lhs_child = child_array[nbodies + 4*(lhs_child - nbodies) + i]
            if new_lhs_child >= 0:
                # Iterating on rhs childs
                for j in range(4):
                    new_rhs_child = child_array[nbodies + 4*(rhs_child - nbodies) + j]
                    if new_rhs_child >= 0:
                        computeForce2_impl(nbodies, child_array, center_of_mass, mass, cell_center, cell_radius, acc, new_lhs_child, next_end_child[i], new_rhs_child, stats)

        return

    ###########################################################################
    # If minimal distance is too high, split the rhs cell
    tmp_theta = cell_radius[rhs_child - nbodies, 0]**2 / 0.5**2
    
    sqr_dist_min = (
          max(abs(cell_center[lhs_child - nbodies, 0] - center_of_mass[rhs_child, 0]) - 0.5*cell_radius[lhs_child - nbodies, 0], 0.)**2
        + max(abs(cell_center[lhs_child - nbodies, 1] - center_of_mass[rhs_child, 1]) - 0.5*cell_radius[lhs_child - nbodies, 1], 0.)**2
    )

    if tmp_theta >= sqr_dist_min:
        
        for i in range(4):
            new_child = child_array[nbodies + 4*(rhs_child - nbodies) + i]
            if new_child >= 0:
                computeForce2_impl(nbodies, child_array, center_of_mass, mass, cell_center, cell_radius, acc, lhs_child, lhs_end_child, new_child, stats)

        return
    
    ###########################################################################
    # If minimal distance in viable and maximal distance is too high, split the lhs cell
    sqr_dist_max = (
          (abs(cell_center[lhs_child - nbodies, 0] - center_of_mass[rhs_child, 0]) + 0.5*cell_radius[lhs_child - nbodies, 0])**2
        + (abs(cell_center[lhs_child - nbodies, 1] - center_of_mass[rhs_child, 1]) + 0.5*cell_radius[lhs_child - nbodies, 1])**2
    )
    
    if tmp_theta >= sqr_dist_max:
        array_pos = nbodies + 4*(lhs_child - nbodies)

        # Calculating next child position
        next_end_child = [lhs_end_child] * 4
        for i in range(2, -1, -1):
            if child_array[array_pos + i + 1] >= 0:
                next_end_child[i] = child_array[array_pos + i + 1]
            else:
                next_end_child[i] = next_end_child[i+1]
        
        # Iterating on lhs childs
        for i in range(4):
            new_child = child_array[nbodies + 4*(lhs_child - nbodies) + i]
            if new_child >= 0:
                computeForce2_impl(nbodies, child_array, center_of_mass, mass, cell_center, cell_radius, acc, new_child, next_end_child[i], rhs_child, stats)

        return
    
    ###########################################################################
    # If both distances are viables, then speed-up things
    # Since the tree is sorted, we should be able to iterate over all stars
    #   of the current lhs cell easily by just knowing the next cell's index.
    # In addition, if the stars where sorted, the loop could be vectorized.
    for i in range(nbodies + 4*(lhs_child - nbodies), nbodies + 4*(lhs_end_child - nbodies)):
        if 0 <= child_array[i] < nbodies:
            Fx, Fy = force(center_of_mass[child_array[i]], center_of_mass[rhs_child], mass[rhs_child])
            acc[child_array[i], 0] += Fx
            acc[child_array[i], 1] += Fy
            stats[3] += 1
            #print('cell2cell')
            print('cell2cell (nbodies = {},lhs_child = {},  rhs_child = {})'.format(nbodies, child_array[i], rhs_child ))
    return


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

