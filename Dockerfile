FROM gcc:15@sha256:eb5e64286ad47187b32bda75c6b6916166ecb41da56559b8b09e0001748d2cce

WORKDIR /app

COPY main.cpp .

RUN g++ -O2 -std=c++20 main.cpp -o main

CMD ["./main"]