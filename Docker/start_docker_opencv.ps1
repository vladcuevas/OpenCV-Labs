docker run `
--rm `
-it `
--name opencv-course `
-v /c/absolute/path/to/pc/directory/:/home/jovyan/work/ `
-p 5000:5000 `
-p 8888:8888 opencvcourses/opencv:4-1-0-conda-dlib /bin/bash