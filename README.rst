
***********************************************************************************************
Using techniques from Reinforcement Learning for Optimally Hyperparametering Video Compression
***********************************************************************************************
.. image:: SBI-logo.svg
    :width: 200px
    :align: right
    :height: 200px
    :alt: SBI Logo

.. image:: https://img.shields.io/badge/dependency-opencv4-brightgreen
    :align: right
    :target: https://opencv.org/opencv-4-0/
    
.. image:: https://img.shields.io/badge/dependency-zlib-brightgreen
    :align: left
    :target: https://docs.python.org/3/library/zlib.html

.. image:: https://img.shields.io/badge/dependency-cryptography-brightgreen
    :align: left
    :target: https://pypi.org/project/cryptography/

.. image:: https://img.shields.io/badge/dependency-FFMPEG-brightgreen
    :align: left
    :target: https://ffmpeg.org/


.. image:: https://img.shields.io/badge/contains-x265-red
    :align: left
    :target: https://bitbucket.org/multicoreware/x265_git.git


-------------------------------------------------------------------

The Presentation can be found in `PPTX <https://github.com/theintrepidthird/SBI-Video-Hackathon/blob/main/report.pptx>`__ and `PDF <https://github.com/theintrepidthird/SBI-Video-Hackathon/blob/main/report.pdf>`__ , as well as in `PDF <https://github.com/theintrepidthird/SBI-Video-Hackathon/blob/main/report(with%20pauses).pdf>`__ with pauses.

This Application has been developed by using Target Networks as commonly used in Reinforcement Learning to learn the optimal parameters that should be fed to HEVC for optimal compression in a particular category of videos, provided a particular type of compression.

    High Efficiency Video Coding (HEVC) is a video compression standard designed as a successor to the widely used Advanced Video Coding (AVC). In comparison to AVC, HEVC offers from 25% to 50% better data compression at the same level of video quality, or substantially improved video quality at the same bit rate.

After Successful HEVC compression for the Video and AAC Compression for the audio, We zip these using the most-efficient standard library available (``zlib``) and use 256-bit AES encryption to encrypt the file.


Installation of Required Libraries
-----------------------------------

You can use pip to download and install the ``zlib`` and ``cryptography`` ::

    pip3 install pyflac
    pip3 install cryptography

You may find instructions on installing ``opencv4`` `here <https://opencv.org/opencv-4-0/>`__.

FFMPEG is a pretty standard library which can be easily installed using ::

    sudo apt install ffmpeg

Installation of these libraries may involve installation of certain intermediaries as well.


Supported platforms 
-------------------

For now

- Linux



Usage
-----

First, You must compile both ``compress.cpp`` and ``decompress.cpp``. This can be done as ::

    g++ -pthread compress.cpp -o compress `pkg-config --libs --cflags opencv4`
    g++ -pthread decompress.cpp -o decompress `pkg-config --libs --cflags opencv4`



For Compression, You need to follow the steps below ::

- Make a list of all files you need to compress in a file (say todo.txt).
- Then Run ./compress todo.txt

Similarly for decompression ::

- Make a list of all the files you need to compress in a file (say todo.txt).
- Then Run ./decompress todo.txt

Results
--------

The File ``phase3.mp4`` which was used for testing can be found `here <https://drive.google.com/file/d/14fxNcPJBfU-HgPigVKemZpu6zYA3YGQZ/view?usp=sharing>`__.
Further, the application is known to process files at speed of about 2 MB/s on Intel(R) Core(TM) i5-1035G1 CPU @ 1.00GHz.

The Application can be toggled between being single-threaded or Multithreaded requires commenting/uncommenting a single line in the main function(s) (line number 173 and 174 in ``compress.cpp`` and line number 72 and 73 in ``decompress.cpp``).

.. note::
    The Software makes use of ``x265`` and ``ffmpeg`` which are under the GNU GPL License.
