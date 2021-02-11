# [Choice] PHP version: 8, 8.0, 7, 7.4, 7.3
ARG VARIANT=7
FROM mcr.microsoft.com/vscode/devcontainers/php:${VARIANT}

# [Option] Install Node.js
ARG INSTALL_NODE="true"
ARG NODE_VERSION="lts/*"
RUN if [ "${INSTALL_NODE}" = "true" ]; then su vscode -c "umask 0002 && . /usr/local/share/nvm/nvm.sh && nvm install ${NODE_VERSION} 2>&1"; fi

# [Optional] Uncomment this section to install additional OS packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

# [Optional] Uncomment this line to install global node packages.
# RUN su vscode -c "source /usr/local/share/nvm/nvm.sh && npm install -g <your-package-here>" 2>&1

ARG GM_VERSION='1.3.36'

WORKDIR /tmp
RUN wget https://sourceforge.net/projects/graphicsmagick/files/graphicsmagick/${GM_VERSION}/GraphicsMagick-${GM_VERSION}.tar.gz/download && \
tar -xvzf download && \
cd GraphicsMagick-${GM_VERSION} && \
./configure --enable-shared --disable-dependency-tracking && \
make && \
make install && \
pwd
#RUN cd GraphicsMagick-${GM_VERSION}
#RUN ./configure --enable-shared --disable-dependency-tracking
#RUN make
#RUN make install