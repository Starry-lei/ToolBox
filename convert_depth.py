import numpy as np
import os
import imageio
from tqdm import tqdm
import io
import cv2

def read_depthdata(depth_path):
    with open(depth_path,'rb') as f:
        data = np.fromfile(f,dtype=np.float32)
        data = data[2:] # try drop first 2
        depth = data.reshape([480,640])
    return depth



def read_rgbdata_opencv(rgb_path):
    image= cv2.imread(rgb_path)
   
    image=np.asarray(image, np.ushort)
    print(image.shape)
    print(image.dtype)


    return image



print(os.getcwd())

scene_path = "/home/lei/Documents/Research/dataset/mannequin_1/"

# depth_path = "depth/"
# new_depth_path = "newdepth/"


rgb_path = "rgb/"
new_RGB_path = "rgb_16bit/"
# new_RGB_path = "test16bit/"

# depth_dirs = os.listdir(scene_path + depth_path)

rgb_dirs = os.listdir(scene_path + rgb_path)


# depth_dir = depth_dirs[0]
rgb_dir = rgb_dirs[0]




for rgb_dir in tqdm(rgb_dirs):

    mypath = scene_path+rgb_path+rgb_dir
    
    mypath_store = scene_path+new_RGB_path+rgb_dir
    # print("show rgb_dir:",mypath)
    rgb_data= read_rgbdata_opencv(mypath)

    # print(rgb_data.shape)

    # normal = img_as_float(io.imread(normal_root+scene_name+normal_dir))
    # plt.imshow(depth)

    # depth = cv2.Mat(depth/5000, cv2.CV_16UC1)
    # depth = (depth*5000).astype(np.ushort) #uint16
    # cv2.imwrite(scene_path+new_depth_path+depth_dir.split(".")[0]+".png",depth)

    rgb_data = (256*rgb_data).astype(np.ushort) #uint16
    print("1 And:" , rgb_data.shape)
    print("2 And:" ,rgb_data.dtype)
    cv2.imwrite(mypath_store,rgb_data)

    # imageio.imwrite(mypath_store,rgb_data)   
    # output = io.BytesIO()
    # imageio.imwrite(output,rgb_data, plugin="pillow", extension=".png")

    
