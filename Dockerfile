ARG MAKE_JOBS=1

FROM buildpack-deps:buster AS cmake

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        cmake \
    && rm -rf /var/lib/apt/lists/*

# Build ITK.
FROM cmake AS itkbuilder
ARG MAKE_JOBS
WORKDIR /opt/itk-src
RUN curl -fsSL https://github.com/InsightSoftwareConsortium/ITK/archive/v4.8.2.tar.gz \
    | tar xz --strip 1 \
    && mkdir build \
    && cd build \
    && cmake \
        -DCMAKE_INSTALL_PREFIX:STRING=/opt/itk \
        -DCMAKE_BUILD_TYPE:STRING=Release \
        -DCMAKE_COLOR_MAKEFILE:BOOL=OFF \
        .. \
    && make --jobs "$MAKE_JOBS" \
    && make install

# Build VTK.
FROM cmake as vtkbuilder
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        qt5-default \
        qt5-qmake \
        qtbase5-dev-tools \
    && rm -rf /var/lib/apt/lists/*
ARG MAKE_JOBS
WORKDIR /opt/vtk-src
RUN curl -fsSL https://github.com/Kitware/VTK/archive/v9.0.1.tar.gz \
    | tar xz --strip 1 \
    && mkdir build \
    && cd build \
    && cmake \
        -DCMAKE_INSTALL_PREFIX:STRING=/opt/vtk \
        -DCMAKE_BUILD_TYPE:STRING=Release \
        -DCMAKE_COLOR_MAKEFILE:BOOL=OFF \
        -DVTK_QT_VERSION:STRING=5 \
        -DVTK_Group_Qt:BOOL=ON \
        -DBUILD_SHARED_LIBS:BOOL=ON \
      .. \
    && make --jobs "$MAKE_JOBS" \
    && make install

FROM cmake as itksnapbuilder
COPY --from=itkbuilder /opt/itk /opt/itk
COPY --from=vtkbuilder /opt/vtk /opt/vtk
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        libfftw3-dev \
        qt5-default \
        qtdeclarative5-dev \
    && rm -rf /var/lib/apt/lists/*
ARG MAKE_JOBS
WORKDIR /opt/itksnap-src
COPY . .
RUN git submodule init \
    && git submodule update \
    && mkdir build \
    && cd build \
    && cmake \
        -DCMAKE_INSTALL_PREFIX:STRING=/opt/itksnap \
        -DCMAKE_BUILD_TYPE:STRING=Release \
        -DCMAKE_COLOR_MAKEFILE:BOOL=OFF \
        -DBUILD_GUI:BOOL=ON \
        -DBUILD_TESTING:BOOL=OFF \
        .. \
    && make --jobs "$MAKE_JOBS"
