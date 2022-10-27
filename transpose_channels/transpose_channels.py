import csv
import pandas as pd
import numpy as np

W2_NC_FILE = "hwc/w2.txt"
W2_CN_FILE = "chw/w2.txt"
W2_N, W2_C = (14, 128)

W5_NC_FILE = "hwc/w5.txt"
W5_CN_FILE = "chw/w5.txt"
W5_N, W5_C = (128, 3)


def transpose_weights(NC_FILE, CN_FILE, N, C):
    print("Load:", NC_FILE)
    df = pd.read_csv(NC_FILE, sep=",", header=None)

    w2_nc = df.to_numpy().reshape((N,C))

    print("Input: NC =", w2_nc.shape)

    print("Transpose...")
    w2_cn = np.transpose(w2_nc, (1,0))

    print("Output: CN =", w2_cn.shape)

    print("Save:", CN_FILE)
    f = open(CN_FILE, "w")
    writer = csv.writer(f)
    w2_cn_flat = w2_cn.reshape(N*C,)
    writer.writerow(w2_cn_flat)
    f.close()


transpose_weights(W2_NC_FILE, W2_CN_FILE, W2_N, W2_C)
transpose_weights(W5_NC_FILE, W5_CN_FILE, W5_N, W5_C)

