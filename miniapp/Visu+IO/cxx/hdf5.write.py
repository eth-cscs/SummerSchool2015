import numpy as np
import h5py
phi = np.fromfile("output.bin", dtype=np.float64, count=-1, sep="")

# create file for writing
out = h5py.File("output.h5","w")
g_id = out.create_group("data")
g_id.create_dataset("phi", (128, 128), np.double, phi)
out.close()
