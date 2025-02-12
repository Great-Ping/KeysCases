FROM ubuntu:20.04

RUN apt-get update && \
    apt-get install -y build-essential gcc && \
    apt-get install -y wget tar

WORKDIR /home/fuzzing-xpdf
# Загрузка xpdf-3.02
RUN wget https://dl.xpdfreader.com/old/xpdf-3.02.tar.gz && \
    tar -xvzf xpdf-3.02.tar.gz

# Сборка и установка
WORKDIR /home/fuzzing-xpdf/xpdf-3.02
RUN ./configure --prefix="/home/fuzzing-xpdf/install/"
RUN make && \
    make install

# Загрузка тестовых pdf    
WORKDIR /home/fuzzing-xpdf/pdf-examples
RUN wget https://github.com/mozilla/pdf.js-sample-files/raw/master/helloworld.pdf && \
    # NOT FOUND    
    # wget http://www.africau.edu/images/default/sample.pdf && \
    wget https://www.melbpc.org.au/wp-content/uploads/2017/10/small-example-pdf-file.pdf



# Локальная установка AFL++
# Зависимости
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential python3-dev automake git flex bison libglib2.0-dev libpixman-1-dev python3-setuptools
RUN apt-get install -y lld-11 llvm-11 llvm-11-dev clang-11 || sudo apt-get install -y lld llvm llvm-dev clang 
RUN apt-get install -y gcc-$(gcc --version|head -n1|sed 's/.* //'|sed 's/\..*//')-plugin-dev libstdc++-$(gcc --version|head -n1|sed 's/.* //'|sed 's/\..*//')-dev
  
# Загрузка AFL
WORKDIR /home
RUN git clone https://github.com/AFLplusplus/AFLplusplus

# Сборка AFL
WORKDIR /home/AFLplusplus
RUN export LLVM_CONFIG="llvm-config-11" && \
    make distrib && \
    make install

# Пересборка XPDF с помощью AFL
# Удаление старых файлов
RUN rm -r /home/fuzzing-xpdf/install
WORKDIR /home/fuzzing-xpdf/xpdf-3.02
RUN make clean

# Сборка с помощью afl-clang-fast
RUN export LLVM_CONFIG="llvm-config-11"
RUN CC=/home/AFLplusplus/afl-clang-fast CXX=/home/AFLplusplus/afl-clang-fast++ ./configure --prefix="/home/fuzzing-xpdf/install/"
RUN make
RUN make install

WORKDIR /home/fuzzing-xpdf/

# Утилита для отладки
RUN apt-get install -y gdb

# afl-fuzz -i /home/fuzzing-xpdf/pdf-examples/ -o /home/fuzzing-xpdf/out/ -s 123 -- /home/fuzzing-xpdf/install/bin/pdftotext @@ /home/fuzzing-xpdf/output
# /home/fuzzing-xpdf/install/bin/pdftotext '/home/fuzzing-xpdf/out/default/crashes/<your_filename>' /home/fuzzing-xpdf/output


# rm -r /home/fuzzing-xpdf/install
# cd /home/fuzzing-xpdf/xpdf-3.02/
# make clean
# CFLAGS="-g -O0" CXXFLAGS="-g -O0" ./configure --prefix="/home/fuzzing-xpdf/install/"
# make
# make install


# gdb --args /home/fuzzing-xpdf/install/bin/pdftotext /home/fuzzing-xpdf/out/default/crashes/id:000000,sig:11,src:000000,time:122111,execs:58055,op:havoc,rep:8 /home/fuzzing-xpdf/output
# run
# bt