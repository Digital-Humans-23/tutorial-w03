import sys
import numpy as np
import importlib.util

from cmake_variables import PYCRL_LIB_PATH

# importing pycrl
spec = importlib.util.spec_from_file_location("pycrl", PYCRL_LIB_PATH)
pycrl = importlib.util.module_from_spec(spec)
sys.modules["module.name"] = pycrl
spec.loader.exec_module(pycrl)

# default window size
DEFAULT_SIZE = 480


class PyCRLEnv:
    def __init__(self):
        self._viewer = None


    def render(self, mode="human", width=DEFAULT_SIZE, height=DEFAULT_SIZE):
        if mode == "human":
            if self._viewer is None:
                # create full-screen viewer
                self._viewer = pycrl.Viewer()

            # show plot for human
            self._viewer.show_plots = False
            self._viewer.render()
        elif mode == "rgb_array":
            if self._viewer is None:
                # create viewer with width and height
                self._viewer = pycrl.Viewer(width, height)

            # hide plot for rgb_array
            self._viewer.show_plots = False
            self._viewer.render()
            size = self._viewer.width, self._viewer.height
            rgb_arr = np.zeros(3 * self._viewer.width * self._viewer.height, dtype=np.uint8)
            self._viewer.read_pixels(rgb_arr)
            data = np.array(rgb_arr, dtype=np.uint8).reshape((size[1], size[0], 3))
            data = np.flip(data, 0)
            return data
        else:
            pass

    def close(self):
        if self._viewer is not None:
            self._viewer.close()
            del self._viewer
            self._viewer = None