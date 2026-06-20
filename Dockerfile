# Linux development and testing environment for SwiftUSD.
#
# On macOS, use https://github.com/apple/container to build and run:
#
#   container build -t swiftusd .
#   container run --rm -it swiftusd bash
#
FROM swift:6.3.2-noble

RUN apt-get update && apt-get install -y --no-install-recommends \
    liblzma-dev \
    libstdc++-12-dev \
    libdeflate-dev \
    libbz2-dev \
    zlib1g-dev \
    python3-dev \
    freeglut3-dev \
    libboost-all-dev \
    libgl1-mesa-dev \
    libgl1-mesa-dri \
    xvfb \
    libxcursor-dev \
    libxt-dev \
    libxi-dev \
    libxinerama-dev \
    libxrandr-dev \
    libgtk-4-dev \
    libgtk-3-dev \
    make \
    git

RUN git clone https://github.com/cpisciotta/xcbeautify.git /xcbeautify && \
    cd /xcbeautify && make install && \
    rm -rf /xcbeautify

RUN git clone https://github.com/wabiverse/SwiftUSD.git /SwiftUSD

WORKDIR /SwiftUSD

RUN swift build --product UsdView | xcbeautify --preserve-unbeautified
