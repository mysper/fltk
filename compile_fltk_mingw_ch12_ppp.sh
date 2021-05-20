
subname=${1##*.}
prename=${1%.*}

g++ -I/usr/local/include -I/usr/local/include/FL/images \
-mwindows -DWIN32 -DUSE_OPENGL32 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE \
-o $prename $1 Graph.cpp Window.cpp GUI.cpp \
-mwindows /usr/local/lib/libfltk_images.a /usr/local/lib/libfltk_png.a \
/usr/local/lib/libfltk_z.a /usr/local/lib/libfltk_jpeg.a \
/usr/local/lib/libfltk.a -lole32 -luuid -lcomctl32
