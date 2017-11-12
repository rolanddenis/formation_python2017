#!/usr/bin/env python
#-*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import matplotlib.animation as animation

class Animation:
    """ Simulation renderer using matplotlib. """

    def __init__(self, simu, axis=[0, 1, 0, 1]):
        """ Initialize an animation view.

        Parameters:
        -----------
        simu: object
            Simulation object with coords and next methods
        axis: list
            Axis bounds [ xmin, xmax, ymin, ymax ].
        """

        self.simu = simu

        self.fig = plt.figure(figsize = (10,10))
        self.ax = self.fig.add_subplot(111)
        self.ax.set_facecolor('black')
        self.ax.axis(axis)

        coords = simu.coords()
        self.scatter = plt.scatter(coords[:,0], coords[:,1], c='white', s=.5)

    def _update_coords(self, i):
        """ Update scatter coordinates. """
        self.simu.next()
        self.scatter.set_offsets(self.simu.coords())
        return self.scatter,

    def main_loop(self):
        """ Simulation main loop. """
        anim = animation.FuncAnimation(self.fig, self._update_coords, blit=True)
        plt.show()


