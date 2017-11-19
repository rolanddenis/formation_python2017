#!/usr/bin/env python
# coding: utf-8

from OpenGL.GL import *
from OpenGL.GLUT import *
import OpenGL.arrays.vbo as glvbo
from OpenGL.GL import shaders

import sys
import math
import numpy as np
import time
from copy import deepcopy


class Axis:
    """ View axis. """
    def __init__(self, origin, scale):
        self.origin = origin
        self.scale = scale


class Animation:
    """ Simulation renderer using OpenGL.

    Press left button to move.
    Press right button to zoom.
    Other shortcuts to control display: 'h' to se the help.


    Under *Windows*, in order to have a working GLUT install,
    follow these instructions:
        https://codeyarns.com/2012/04/27/pyopengl-installation-notes-for-windows/
        https://deparkes.co.uk/2015/02/04/anaconda-whl-install/
    1) uninstall pyopengl and pyopengl-accelerate Python modules,
    2) download appropriate files (windows and python versions) from
        https://www.lfd.uci.edu/~gohlke/pythonlibs/#pyopengl,
    3) install it using 'pip install <file>' (even if you use Anaconda).


    Freely inspired from:
        http://cyrille.rossant.net/2d-graphics-rendering-tutorial-with-pyopengl/
        https://sites.google.com/site/dlampetest/python/vectorized-particle-system-and-geometry-shaders
        http://carloluchessa.blogspot.fr/2012/09/simple-viewer-in-pyopengl.html
    """

    def __init__(self, simu,
                 axis=[0, 1, 0, 1], size=[640, 480], title=b"Animation",
                 use_colors=False, update_colors=False,
                 use_adaptative_opacity=False, start_paused=False):
        """ Initialize an animation view.

        Parameters:
        -----------
        simu: object
            Simulation object with coords and next methods
        axis: list
            Axis bounds [ xmin, xmax, ymin, ymax ].
        size: list
            Initial window size [width, height].
        title: string
            Window title.
        use_colors: bool
            True to colorize the stars using simu.colors method.
        update_colors: bool
            True if the color must be update at each frame (and not only at
                the initialisation).
        use_adaptative_opacity: bool
            True if the opacity is adapted to the view zoom.
        start_paused: bool
            True if the simulation is initially paused.
        """

        self.simu = simu
        self.axis = Axis([axis[0], axis[2]], max((axis[1]-axis[0])/size[0],
                                                 (axis[3]-axis[2])/size[1]))
        self.size = size
        self.mouse_action = None

        # Initialize the OpenGL Utility Toolkit
        glutInit(sys.argv)

        # Initial display mode (RGBA colors and double buffered window)
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE)

        # Initial window
        glutInitWindowSize(size[0], size[1])
        glutInitWindowPosition(0, 0)
        glutCreateWindow(title)

        # Callbacks
        glutDisplayFunc(self._draw)         # When the window must be redrawn
        glutIdleFunc(self.draw_next_frame)  # When OpenGL gets bored
        glutReshapeFunc(self._resize)       # When the window is resized
        glutMouseFunc(self._mouse)          # When a mouse button is pressed/released
        glutMotionFunc(self._motion)        # When the mouse moves with a pressed button
        glutKeyboardFunc(self._keyboard)    # When a key is pressed

        # Create a Vertex Buffer Object for the vertices
        coords = simu.coords()
        self.vbo_vertex = glvbo.VBO(coords)
        self.count = coords.shape[0]

        # Display options
        self.use_colors_update = update_colors
        self.use_colors = use_colors
        self.adaptative_opacity_factor = self.axis.scale
        self.use_fps = True
        self.is_paused = start_paused

    ###########################################################################
    # Properties

    @property
    def use_colors(self):
        """ Control color display. """
        try:
            return self._use_colors
        except AttributeError:
            return False

    @use_colors.setter
    def use_colors(self, value):
        self._use_colors = value

        if self._use_colors:
            try:
                if self.use_colors_update or not hasattr(self, 'vbo_color'):
                    self._update_colors()
                glEnableClientState(GL_COLOR_ARRAY)
            except AttributeError:
                self._use_colors = False

        if not self._use_colors:
            glDisableClientState(GL_COLOR_ARRAY)

    @property
    def use_colors_update(self):
        """ Control color update for each frame. """
        try:
            return self._use_colors_update
        except AttributeError:
            return False

    @use_colors_update.setter
    def use_colors_update(self, value):
        self._use_colors_update = value

    @property
    def use_fps(self):
        """ Control the display of the fps. """
        try:
            return self._use_fps
        except AttributeError:
            return False

    @use_fps.setter
    def use_fps(self, value):
        self._use_fps = value

        if self._use_fps:
            # To calculate the fps
            self.frame_times = [time.time()] * 50
            self.frame_id = 0

    @property
    def is_paused(self):
        """ Control the execution of the simulation. """
        try:
            return self._is_paused
        except AttributeError:
            return False

    @is_paused.setter
    def is_paused(self, value):
        self._is_paused = value

    @property
    def use_help(self):
        """ Control help display. """
        try:
            return self._use_help
        except AttributeError:
            return False

    @use_help.setter
    def use_help(self, value):
        self._use_help = value

    @property
    def use_adaptative_opacity(self):
        """ Control the adaptive opacity.

        Opacity varies linearly with the zoom factor.
        """
        try:
            return self._use_adaptative_opacity
        except AttributeError:
            return False

    @use_adaptative_opacity.setter
    def use_adaptative_opacity(self, value):
        self._use_adaptative_opacity = value

        if value and not hasattr(self, '_ao_shader_program'):
            # Try except ?
            glEnable(GL_PROGRAM_POINT_SIZE)
            glEnable(GL_POINT_SPRITE)
            vertex_shader = shaders.compileShader("""
                uniform float scale;
                uniform float scale2;
                void main()
                {
                    gl_Position = ftransform();
                    gl_FrontColor = gl_Color;
                    gl_FrontColor[3] = min(1., gl_FrontColor[3]*scale);
                    gl_PointSize = max(1., 21.*scale);
                    gl_Position -= vec4(1.,1.,0.,0.)*gl_PointSize*scale2 * 0.5;
                    //gl_Position -= vec4(1.,1.,0.,0.)*gl_PointSize* 0.5;
                }
                """, GL_VERTEX_SHADER)

            fragment_shader = shaders.compileShader("""
                #version 120
                uniform float scale;
                void main()
                {
                    gl_FragColor = gl_Color;
                    float dist = length(gl_PointCoord - vec2(0.5, 0.5));
                    if (dist > 0.6/(21.*scale))
                        gl_FragColor[3] = max(0., 5e-3/dist - 0.01);
                }
                """, GL_FRAGMENT_SHADER)

            self._ao_shader_program = shaders.compileProgram(vertex_shader, fragment_shader)
            
            vertex_shader2 = shaders.compileShader("""
                uniform float scale;
                void main()
                {
                    gl_Position = ftransform();
                    gl_FrontColor = gl_Color;
                    gl_FrontColor[3] = min(1., gl_FrontColor[3]*scale);
                    gl_PointSize = 1.;
                }
                """, GL_VERTEX_SHADER)

            fragment_shader2 = shaders.compileShader("""
                #version 120
                uniform float scale;
                void main()
                {
                    gl_FragColor = gl_Color;
                }
                """, GL_FRAGMENT_SHADER)
            self._ao_shader_program2 = shaders.compileProgram(vertex_shader2, fragment_shader2)

    @property
    def adaptative_opacity_factor(self):
        """ Control the adaptative opacity amplitude.

        For a given view/zoom, setting this factor to
        the ratio between the axis width/height and
        the screen width/height (i.e. the zoom factor)
        doesn't change the display.
        """
        try:
            return self._ao_factor
        except AttributeError:
            return self.axis.scale

    @adaptative_opacity_factor.setter
    def adaptative_opacity_factor(self, value):
        self._ao_factor = value

    @property
    def tracked_star(self):
        """ Id of the tracked star. None if disabled. """
        try:
            return self._tracked_star
        except AttributeError:
            return None

    @tracked_star.setter
    def tracked_star(self, value):
        self._tracked_star = value

    ###########################################################################
    # Public methods

    def main_loop(self):
        """ Simulation main loop. """
        glutMainLoop()

    def draw_next_frame(self):
        """ Update simulation data and display it. """
        if not self.is_paused:
            self.simu.next()
            self._update_coords()

            if self.use_colors and self.use_colors_update:
                self._update_colors()

        glutPostRedisplay()

    def reset_view(self):
        """ Reset view accordingly to the particle coordinates and the tracked star. """
        border = 0.1
        coords = self.simu.coords()
        coord_min = coords.min(axis=0)
        coord_max = coords.max(axis=0)

        if self.tracked_star is None:
            center = 0.5 * (coord_min + coord_max)
        else:
            center = coords[self.tracked_star]

        axis_size = 2 * np.maximum(center - coord_min, coord_max - center)
        self.axis.scale = (1. + 2*border) * np.max(axis_size / self.size)
        self.center_view(*center)

    def center_view(self, x, y):
        """ Center view on the given axis coordinates. """
        self.axis.origin = [
            x - 0.5 * self.size[0]*self.axis.scale,
            y - 0.5 * self.size[1]*self.axis.scale
        ]

    ###########################################################################
    # Internal methods

    def _update_coords(self):
        """ Update vertex coordinates. """
        coords = self.simu.coords()
        self.vbo_vertex.set_array(coords)
        self.count = coords.shape[0]

        # Centering view on tracked star
        if self.tracked_star is not None:
            self.center_view(*coords[self.tracked_star])

    def _update_colors(self):
        """ Update or create Vertex Buffer Object of colors. """
        colors = self.simu.colors()

        try:
            self.vbo_color.set_array(colors)
        except AttributeError:
            self.vbo_color = glvbo.VBO(colors)

        self.vbo_color.bind()
        if colors.shape[1] == 3:
            glColorPointer(3, GL_DOUBLE, 0, None)
        else:
            glColorPointer(4, GL_DOUBLE, 0, None)

    def _mouse(self, button, state, x, y):
        """ Called when a mouse button has been pressed/released. """
        if self.mouse_action is None and state == GLUT_DOWN:
            self.button = button
            self.old_axis = deepcopy(self.axis)
            self.x_start = x
            self.y_start = y

            if button == GLUT_LEFT_BUTTON:
                self.mouse_action = 'move'
            elif button == GLUT_RIGHT_BUTTON:
                self.mouse_action = 'zoom'

        elif self.mouse_action is not None and state == GLUT_UP and button == self.button:
            self.mouse_action = None

    def _motion(self, x, y):
        """ Called when the mouse has move while a button is pressed. """
        if self.mouse_action == 'move':
            self.axis.origin[0] = self.old_axis.origin[0] - self.old_axis.scale * (x - self.x_start)
            self.axis.origin[1] = self.old_axis.origin[1] + self.old_axis.scale * (y - self.y_start)

        elif self.mouse_action == 'zoom':
            zoom_factor = math.exp(0.01 * (self.y_start - y))
            self.axis.origin[0] = self.old_axis.origin[0] + (1 - zoom_factor) * self.old_axis.scale * self.x_start
            self.axis.origin[1] = self.old_axis.origin[1] + (1 - zoom_factor) * self.old_axis.scale * (self.size[1]-self.y_start)
            self.axis.scale = zoom_factor * self.old_axis.scale

        glutPostRedisplay()

    def _keyboard(self, key, x, y):
        """ Called when a key is pressed. """
        if key == b'r':
            self.reset_view()
        elif key == b'q':
            glutLeaveMainLoop()
        elif key == b'f':
            self.use_fps = not self.use_fps
        elif key == b'c':
            self.use_colors = not self.use_colors
        elif key == b'u':
            self.use_colors_update = not self.use_colors_update
        elif key == b'o':
            self.use_adaptative_opacity = not self.use_adaptative_opacity
        elif key == b't':
            self.tracked_star = self._find_nearest_star(x, y)
        elif key == b'T':
            self.tracked_star = None
        elif key == b'p' or key == b' ':
            self.is_paused = not self.is_paused
        elif key == b'h':
            self.use_help = not self.use_help

    def _resize(self, width, height):
        """ Called when the window is resized. """
        self.size = [max(width, 1), max(height, 1)]

        # Update the viewport
        glViewport(0, 0, self.size[0], self.size[1])

    def _print(self, text, pos=[0, 0], color=[1., 1., 1., 1.]):
        """ Print a text. """

        # Default position is the top-left corner
        pos = [self.axis.origin[0] + 9*pos[0]*self.axis.scale,
               self.axis.origin[1] + (self.size[1] - 15*(pos[1]+1))*self.axis.scale]

        glColor4f(*color)
        glRasterPos2f(*pos)

        for char in text:
            if char == "\n":
                pos[1] -= 15*self.axis.scale
                glRasterPos2f(*pos)
            else:
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ord(char))

    def _print_help(self):
        """ Print help. """
        self._print(pos=[0, 1], text="""left click: translate view
right click: zoom in/out
r: reset view
q: quit
f: toggle fps display
c: toggle colors display
u: toggle colors update
o: toggle adaptative opacity
t: track nearest star
T: disable tracking
p: pause (or <space>)
h: toggle help display""")

    def _fps(self):
        """ Update frame time and id and return the fps. """
        curr_time = time.time()
        duration = curr_time - self.frame_times[self.frame_id]
        self.frame_times[self.frame_id] = curr_time
        self.frame_id = (self.frame_id + 1) % len(self.frame_times)

        return len(self.frame_times) / duration

    def _print_fps(self):
        """ Calculate and print fps. """
        self._print("{:.1f}fps".format(self._fps()))

    def _find_nearest_star(self, x, y):
        """ Return the index of the nearest star from mouse coordinates. """
        mouse_pos = self.axis.origin + self.axis.scale * np.asarray([x, self.size[1]-y])
        return ((self.simu.coords() - mouse_pos) ** 2).sum(axis=1).argmin()

    def _activate_adaptative_opacity(self):
        """ Activate the adaptative opacity shader program. """

        glEnable(GL_PROGRAM_POINT_SIZE)
        glEnable(GL_POINT_SPRITE)

        glUseProgram(self._ao_shader_program)
        glUniform1f(glGetUniformLocation(self._ao_shader_program, 'scale'),
                     np.float32(max(0.01, self._ao_factor/self.axis.scale)))
        glUniform1f(glGetUniformLocation(self._ao_shader_program, 'scale2'),
                     np.float32(self.axis.scale))
        glDrawArrays(GL_POINTS, 0, self.count)
        glUseProgram(self._ao_shader_program2)
        glUniform1f(glGetUniformLocation(self._ao_shader_program2, 'scale'),
                     np.float32(max(0.01, self._ao_factor/self.axis.scale)))

    def _draw(self):
        """ Called when the window must be redrawn. """

        # Alpha blending
        glDisable(GL_DEPTH_TEST)
        glEnable(GL_BLEND)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)

        # Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT)

        # Update perspective transformation
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        glOrtho(self.axis.origin[0], self.axis.origin[0] + self.axis.scale * self.size[0],
                self.axis.origin[1], self.axis.origin[1] + self.axis.scale * self.size[1],
                -1, 1)

        # Adaptative opacity
        if self.use_adaptative_opacity:
            self._activate_adaptative_opacity()
        else:
            glUseProgram(0)

        # Background color
        glClearColor(0., 0., 0., 0.)

        # Draw color
        glColor(1., 1., 1.)

        # Bind the vertex VBO
        self.vbo_vertex.bind()

        # Tell OpenGL that the VBO contains an array of vertices
        glEnableClientState(GL_VERTEX_ARRAY)

        # These vertices contain 2 double precision coordinates
        glVertexPointer(2, GL_DOUBLE, 0, None)

        # Adaptative opacity
        if self.use_adaptative_opacity:
            self._activate_adaptative_opacity()
        else:
            glUseProgram(0)

        # Draw "count" points from the VBO
        glDrawArrays(GL_POINTS, 0, self.count)

        # Printing fps
        if self.use_fps:
            self._print_fps()

        # Printing help
        if self.use_help:
            self._print_help()

        # Swap display buffers
        glutSwapBuffers()


###############################################################################
# Demo
if __name__ == '__main__':
    """ Demo """
    import numpy as np

    class SpinningCloud:
        def __init__(self, size, theta=math.pi/18000):
            self._coords = np.random.randn(size, 2)
            self._colors = np.random.rand(size, 4)
            self._rot = np.asarray([[math.cos(theta), math.sin(theta)],
                                    [-math.sin(theta), math.cos(theta)]])

        def next(self):
            self._coords = np.dot(self._coords, self._rot)

        def coords(self):
            return self._coords

        def colors(self):
            return self._colors

    simu = SpinningCloud(100000, math.pi/1800)

    anim = Animation(simu, axis=[-2, 2, -2, 2], size=[480, 480])
    anim.use_colors = True
    anim.use_colors_update = False
    anim.use_adaptative_opacity = True
    anim.use_help = True

    anim.main_loop()
