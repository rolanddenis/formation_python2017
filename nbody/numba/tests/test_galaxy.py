import numpy as np
import sys
import math

import nbody
#from nbody.naive import compute_energy
from nbody.barnes_hut_array import compute_energy
from nbody.barnes_hut_array import quadArray

def temp2color(temps):
    """ Convert black body temperature to corresponding RGBA color.

    See http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/
    """
    colors = np.empty((temps.size, 4))
    scaled_temps = temps/100.

    # Red component
    ind = scaled_temps <= 66.
    colors[ind, 0] = 255.
    colors[~ind, 0] = 329.698727446 * ((scaled_temps[~ind] - 60.) ** -0.1332047592)

    # Green component
    colors[ind, 1] = 99.4708025861 * np.log(scaled_temps[ind]) - 161.1195681661
    colors[~ind, 1] = 288.1221695283 * ((scaled_temps[~ind] - 60.) ** -0.0755148492)

    # Blue component
    ind = scaled_temps >= 66.
    colors[ind, 2] = 255.
    colors[~ind, 2] = 138.5177312231 * np.log(scaled_temps[~ind] - 10.) - 305.0447927307
    colors[scaled_temps <= 19., 2] = 0.

    # Alpha component
    colors[:, 3] = 255.

    # Clipping values
    np.clip(colors/255., 0., 1., out=colors)

    return colors


class Galaxy:
    def __init__(self, blackHole, dt = 1., display_step = 1):
        self.mass, self.particles = nbody.init_collisions(blackHole)
        self.time_method = nbody.ADB6(dt, self.particles.shape[0], compute_energy)
        self.display_step = display_step
        self.it = 0
        self.mean_density = np.zeros(self.particles.shape[0])

    def next(self):
        for i in range(self.display_step):
            self.it += 1
            print(self.it)
            self.time_method.update(self.mass, self.particles)

    def coords(self):
        return self.particles[:, :2]

    def colors(self):
        """
        speed_magnitude = np.linalg.norm(self.particles[:, 2:4], axis=1)
        colors = temp2color( 3000 + 6000*speed_magnitude/speed_magnitude.max() )
        colors[:,3] = 0.05
        return colors + np.asarray([0., 0., 0., 0.95]) * np.minimum(self.mass, 20).reshape(-1, 1) / 20
        """

        bmin = np.min(self.particles[: ,:2], axis=0)
        bmax = np.max(self.particles[: ,:2], axis=0)
        root = quadArray(bmin, bmax, self.particles.shape[0])
        root.buildTree(self.particles)
        cell_radius = np.linalg.norm(root.cell_radius[root.child[0:self.particles.shape[0]]], axis=1)
        self.mean_density += 1e-2*(self.mass/cell_radius - self.mean_density)
        temps = np.minimum(9000, np.maximum(1001, 9000 - 0.8e3*np.log(self.mean_density)))
        print( np.min(self.mean_density), np.max(self.mean_density))
        print( np.min(temps), np.max(temps))
        colors = temp2color(temps)
        colors[:,3] = 0.05 + 0.95*((temps-1000)/8000)**2
        return colors


if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--render', default='matplotlib', help='Animation renderer')
    parser.add_argument('--display_step', type=int, default=5, help='Simulation steps between each render')
    args = parser.parse_args()

    sys.path.append(args.render)
    from animation import Animation

    np.random.seed(42)

    blackHole = [
                #{'coord': [0, 0], 'mass': 1000000, 'svel': 1, 'stars': 2000, 'radstars': 3},
                #{'coord': [3, 3], 'mass': 1000000, 'svel': 0.9, 'stars': 1000, 'radstars': 1}
                {'coord': [0, 0], 'mass': 1000000, 'svel': 1, 'stars': 6000, 'radstars': 6},
                {'coord': [8, 8], 'mass': 1000000/2, 'svel': 1, 'stars': 1000, 'radstars': 1}
                ]
    sim = Galaxy(blackHole, display_step = args.display_step)

    anim = Animation( sim, axis=[-10., 10., -10., 10.] )

    if args.render == 'opengl':
        anim.use_colors = True
        anim.use_colors_update = False
        anim.use_adaptative_opacity = True
        anim.use_pixel_render = False
        anim.use_nebulae_render = True

    anim.main_loop()

