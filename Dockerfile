FROM python:3.8.2

WORKDIR /app
ADD node.py .
EXPOSE 8000

CMD ["python", "./node.py"]

#FROM gcc:latest
#WORKDIR /app
#ADD cnode.cpp .
#EXPOSE 8000

#CMD ["g++", "./cnode.cpp"]