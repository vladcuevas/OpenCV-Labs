# Contrast Limited Adaptive Histogram Equalization (CLAHE)

Histogram equalization uses the pixels of the entire image to improve contrast. While this may look good in many cases, sometimes we may want to enhance the contrast locally so the image does not looks more natural and less dramatic.

For such applications, we use [Contrast Limited Adaptive Histogram Equalization (CLAHE)](https://docs.opencv.org/4.1.0/d5/daf/tutorial_py_histogram_equalization.html) which improves the local contrast. More importantly it allows us to specify the size of the neighborhood that is considered "local".

Let's pick a different image, where we may prefer [CLAHE](https://en.wikipedia.org/wiki/Adaptive_histogram_equalization#Contrast_Limited_AHE) in place of regular histogram equalization.
