#include <bits/stdc++.h>	
#include <opencv2/opencv.hpp>	
#include <unistd.h>	
#include <zmq.hpp>	
using namespace std;

int main() {	

	std::string command="send_picture";	
    zmq::context_t context(3);	
    zmq::socket_t socket(context, ZMQ_REP);	
    zmq::message_t reply, request;	
    socket.bind("tcp://*:5555");	

     socket.recv(&request);	
    while (true) {	
      //  command = read_command();	
        std::cout << "command: " << command << std::endl;	
        send_msg(socket, command);	
        if (command == "send_picture") {	
            //下位机发图，上位机收图	
            //收人脸数	
            socket.recv(&request);	
            int face_num =	
                std::stoi(std::string((char *)request.data(), request.size()));	
            send_msg(socket, "received_face_num");	
            //人脸名字	
            socket.recv(&request);	
            std::string name =	
                std::string((char *)request.data(), request.size());	
            send_msg(socket, "received_face_name");	
            //收图片	
            cv::Mat img;	
            for (int i = 0; i <= face_num; i++) {	
                socket.recv(&request);	
                std::vector<uchar> img_data(request.size());	
                memcpy(img_data.data(), request.data(), request.size());	
                img = cv::imdecode(img_data, cv::IMREAD_COLOR);	
                imwrite("" + to_string(i) + ".jpg", img);	
                send_msg(socket, "reveice_picture_i");	
            }	
            socket.recv(&request);	
        } else if (command == "none") {	
            socket.recv(&request);	
        } else if (command == "start_traning") {	
            //收	
            socket.recv(&request);	
        } else if (command == "change_train_set") {	
            socket.recv(&request);	
            //发人名	
            std::string human_name = "hhh";	
            send_msg(socket, human_name);	
            //收	
            socket.recv(&request);	
            //发照片名字	
//             std::string picture_name = "1.jpg";	
//             send_msg(socket, picture_name);	
            //收	
//             socket.recv(&request);	
            //发送图片	
            send_pic(socket, "../pic/1.png");	
            //收	
            socket.recv(&request);	
        } else {	
            std::cout << "GGGGGGGGGGGGGGGGGGGGGGGGGG" << std::endl;	
        }	
    }	
    return 0;	
}