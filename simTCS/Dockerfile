FROM centos:7

# Update mirrors to use vault
RUN sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* && \
    sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

# Install build essentials
RUN yum update -y && yum install -y \
    wget \
    gcc \
    gcc-c++ \
    make \
    readline-devel \
    perl \
    && yum clean all

# Download and build EPICS base
WORKDIR /epics
RUN wget https://github.com/epics-base/epics-base/archive/refs/tags/R7.0.8.tar.gz \
    && tar xzf R7.0.8.tar.gz \
    && mv epics-base-R7.0.8 base \
    && cd base \
    && make

# Create IOC directory
WORKDIR /opt/ioc
COPY simTCS.db .
COPY st.cmd .
RUN chmod +x st.cmd

# Set environment variables
ENV EPICS_BASE=/epics/base
ENV EPICS_HOST_ARCH=linux-x86_64
ENV PATH="${EPICS_BASE}/bin/${EPICS_HOST_ARCH}:${PATH}"

CMD ["/opt/ioc/st.cmd"]
