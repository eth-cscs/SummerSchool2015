import numpy as np
import h5py

input = h5py.File("output.h5","r")
input.values()
input['data']
input['data'].values()
phi = input['data']['phi']

