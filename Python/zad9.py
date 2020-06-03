import matplotlib.image as mpimg
import matplotlib.pyplot as plt
import copy
import numpy as np

#diff = 0.2
diffPer = 0.6
diffVect = 0.25


img = mpimg.imread('wroclaw.png')
img2 = np.ones((img.shape[0], img.shape[1], 3))
img3 = np.ones((img.shape[0], img.shape[1], 3))


"""
def finddiff(image, i, j, l):
    tab = image[i, j]
    for m in range(-1, 2):
        for n in range(-1, 2):
            if (i == 0 and m < 0) or (i == img.shape[0] and m > 0):
                continue
            if (j == 0 and n < 0) or (j == img.shape[1] and n > 0):
                continue
            if m == n and m == 0:
                continue
            if image[i+m, j+n, l] - tab[l] > diff:
                return True
    return False
    
    img2 = copy.copy(img)
        change = False
        for l in range(3):
            if finddiff(img, i, j, l):
                img2[i, j] = [0, 0, 0]
                change = True
                break
        if not change:
            img2[i, j] = [1, 1, 1]
"""


def finddiff2(image, i, j):
    tab = image[i, j]
    for l in range(0,3):
        for m in range(-1, 2):
            for n in range(-1, 2):
                if m == n == 0:
                    continue
                if tab[l] == 0 or abs(image[i+m, j+n, l] - tab[l])/tab[l] > diffPer:
                    img2[i + m, j + n] = [0, 0, 0]
                    img2[i, j] = [0, 0, 0]
                    return


def finddiff3(image, i, j):
    tab = image[i, j]
    for m in range(-1, 2):
        for n in range(-1, 2):
            if m == n == 0:
                continue
            if np.linalg.norm(image[i+m, j+n] - tab) > diffVect:
                img3[i+m, j+n] = [0, 0, 0]
                img3[i, j] = [0, 0, 0]


for i in range(1, img.shape[0]-1):
    for j in range(1, img.shape[1]-1):
        if np.any(img2[i, j] == 1):
            finddiff2(img, i, j)
        if np.any(img3[i, j] == 1):
            finddiff3(img, i, j)

f, plot = plt.subplots(3)
plot[0].imshow(img)
plot[1].imshow(img2)
plot[2].imshow(img3)
plt.show()


