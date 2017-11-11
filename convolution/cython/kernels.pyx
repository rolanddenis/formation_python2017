# cython: boundscheck=False, wraparound=False
from cython.parallel import parallel, prange
import numpy as np
cimport cython

from libc.math cimport fabs

"""
Definit une convolution faisant une moyenne des voisins d'un pixel donne
( stencil de 3x3 )
"""
def convolve_mean2( image):
    cdef int height, width
    height, width = image.shape
    out_image = np.empty((height-2,width-2))
    
    cdef double[:,::1] iview = image
    cdef double[:,::1] oview = out_image
    
    cdef int i, j
    #for i in range(height-2):
    for i in prange(0, height-3, nogil=True):
        for j in range(width-2):
            oview[i,j] = 0.25 * ( iview[i,j+1] + iview[i+2,j+1] + iview[i+1,j] + iview[i+1,j+2] )
    
    #out_image[:, :] = 0.25*(image[:-2,1:-1]+image[2:,1:-1]+image[1:-1,:-2]+image[1:-1,2:])
    return out_image

def convolve_mean3(image):
    cdef int height, width, dim
    height, width, dim = image.shape
    out_image = np.empty((height-2,width-2, dim))
    
    cdef double[:,:,:] iview = image
    cdef double[:,:,:] oview = out_image
    
    cdef int i, j
    for i in range(height-2):
        for j in range(width-2):
            for k in range(dim):
                oview[i,j,k] = 0.25 * ( iview[i,j+1,k] + iview[i+2,j+1,k] + iview[i+1,j,k] + iview[i+1,j+2,k] )   
    
    return out_image

"""
Definie l'operateur laplacien comme convolution : permet de detecter les bords dans une image
"""
def convolve_laplacien2(image):
    cdef int height, width
    height, width = image.shape
    out_image = np.empty((height-2,width-2))
    
    cdef double[:,::1] iview = image
    cdef double[:,::1] oview = out_image
    
    cdef int i, j
    for i in range(height-2):
        for j in range(width-2):
            oview[i,j] = fabs( 4*iview[i+1,j+1] - iview[i,j+1] - iview[i+2,j+1] - iview[i+1,j] - iview[i+1,j+2] )
            
    # On renormalise l'image :
    valmax = np.max(out_image)
    valmax = max(1.,valmax)+1.E-9
    out_image *= 1./valmax
    return out_image

def convolve_laplacien3(image):
    cdef int height, width, dim
    height, width, dim = image.shape
    out_image = np.empty((height-2,width-2, dim))
    
    cdef double[:,:,:] iview = image
    cdef double[:,:,:] oview = out_image
    
    cdef int i, j, k
    for i in range(height-2):
        for j in range(width-2):
            for k in range(dim):
                oview[i,j,k] = abs( 4*iview[i+1,j+1,k] - iview[i,j+1,k] - iview[i+2,j+1,k] - iview[i+1,j,k] - iview[i+1,j+2,k] )
            
    # On renormalise l'image :
    valmax = np.max(out_image)
    valmax = max(1.,valmax)+1.E-9
    out_image *= 1./valmax
    return out_image

"""
Convolution generale avec une taille de stencil quelconque. Permet de definir tous les stencils que l'on souhaite !
"""
def convolve_matrix2(image, convolution_array) :
    cdef int height, width    
    height, width= image.shape
    cdef int nx     = convolution_array.shape[1]
    cdef int ny     = convolution_array.shape[0]
    cdef int half_x = nx//2
    cdef int half_y = ny//2
    out_image = np.zeros((height-nx+1,width-ny+1))
    cdef int h, w   
    h, w = out_image.shape
    
    cdef double[:,:] iview = image
    cdef double[:,:] oview = out_image
    cdef double[:,:] cview = convolution_array

    cdef int jw, iw, jjw, iiw
    for jw in range(ny):
        for iw in range(nx):
            for jjw in range(h):
                for iiw in range(w):
                    oview[jjw,iiw] += cview[jw,iw]*iview[jw+jjw,iw+iiw]

    # On renormalise l'image en ramenant les valeurs des couleurs entre 0 et 1
    out_image = np.abs(out_image)
    valmax = np.max(out_image)
    valmax = max(1.,valmax)+1.E-9
    out_image *= 1./valmax
    return out_image

def convolve_matrix3(image, convolution_array) :
    height, width, dim = image.shape
    nx     = convolution_array.shape[1]
    ny     = convolution_array.shape[0]
    half_x = nx//2
    half_y = ny//2
    out_image = np.zeros((height-nx+1,width-ny+1, dim))
    h, w, d = out_image.shape

    for jw in range(0,ny):
        for iw in range(0,nx):
            out_image[:,:,:] += convolution_array[jw,iw]*image[jw:jw+h,iw:iw+w,:]

    # On renormalise l'image en ramenant les valeurs des couleurs entre 0 et 1
    out_image = np.abs(out_image)
    valmax = np.max(out_image)
    valmax = max(1.,valmax)+1.E-9
    out_image *= 1./valmax
    return out_image

