from PIL import Image
import math
import os


slice_size = 16


def slice_img(image_path, out_name, out_dir, padding):
  img = Image.open(image_path)
  width, height = img.size
  upper = 0
  left = 0
  count = 3456
  while upper < height:
    while left < width:
      bbox = (left, upper, left + slice_size, upper + slice_size)
      working_slice = img.crop(bbox)
      print("Dang chay " + str(count))
      working_slice.save(os.path.join(out_dir + "/" + out_name, str(count) + '.png'))
      count = count + 1

      
      left += slice_size
    upper += slice_size
    left = 0

if __name__ == '__main__':

  image_path = input("Nhap duong dan: ")
  out_name = input("Nhap ten file: ")
  out_dir = os.getcwd()

  slice_img(out_dir + "/" + image_path, out_name, out_dir, 0)
