FROM ubuntu:latest

# Install dependencies
RUN apt-get update && apt-get install -y \
    gcc \
    make \
    readline-common \
    libreadline-dev \
    libc6-dev \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source files
COPY . .

# Update readline paths for Ubuntu
RUN sed -i 's|-L /Users/$(USER)/Desktop/homebrew/opt/readline/lib|-L /usr/lib/x86_64-linux-gnu|g' Makefile && \
    sed -i 's|-I /Users/$(USER)/Desktop/homebrew/opt/readline/include|-I /usr/include|g' Makefile

# Build the project
RUN make clean && make

# Set the entrypoint
ENTRYPOINT ["./minishell"]