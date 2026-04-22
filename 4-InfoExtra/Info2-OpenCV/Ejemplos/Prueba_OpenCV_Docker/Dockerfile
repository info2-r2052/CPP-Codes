FROM robtry/opencv-420

COPY . /root/workspace

WORKDIR /root/workspace

RUN mkdir imagen

RUN g++ main.cpp -o output.e `pkg-config --cflags --libs opencv4`

CMD ["./output.e"]

 