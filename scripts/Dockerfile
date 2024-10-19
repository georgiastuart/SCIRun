# syntax=docker/dockerfile:1.3-labs
FROM ubuntu:24.04

RUN apt-get update && \
  DEBIAN_FRONTEND=noninteractive TZ=Etc/UTC apt-get install -y \
  git build-essential cmake \
  qtbase5-dev libqt5svg5-dev zlib1g-dev wget libssl-dev

ARG SCIRUN_VERSION="5.0-beta.2023"
WORKDIR /scirun-src 
RUN wget https://github.com/SCIInstitute/SCIRun/archive/refs/tags/v${SCIRUN_VERSION}.tar.gz -O scirun.tar.gz \
  && tar --strip-components=1 -xvf scirun.tar.gz

ENV MAKEFLAGS="-j8"
WORKDIR /scirun 
RUN cmake -DQt_PATH=/usr/lib/x86_64-linux-gnu/cmake -DCMAKE_BUILD_TYPE=Release \
  /scirun-src/Superbuild \
  && make

ENV PATH="/scirun/SCIRun:/scirun/Externals/Install/Python_external/bin:$PATH"
ENV LD_LIBRARY_PATH="/scirun/SCIRun/lib:/scirun/Externals/Install/Python_external/lib:$LD_LIBRARY_PATH"

# RUN python3 -m ensurepip --upgrade && pip3 install uncertainsci
RUN python3 -m venv --upgrade-deps venv && . venv/bin/activate && pip install uncertainsci
RUN rm -r /scirun-src 
RUN cat <<'EOF' > /scirun/entrypoint.sh
#!/bin/sh
. /scirun/venv/bin/activate
exec "$@"
EOF

RUN chmod a+x /scirun/entrypoint.sh

WORKDIR /data 
ENV QT_DEBUG_PLUGINS=1
ENTRYPOINT [ "/scirun/entrypoint.sh" ]
CMD [ "/scirun/SCIRun/SCIRun" ]

