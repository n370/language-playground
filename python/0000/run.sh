#!/bin/bash
python 0000.py
ffmpeg -framerate 60 -i frame_%04d.png -c:v libx264 -pix_fmt yuv420p output_video.mp4
