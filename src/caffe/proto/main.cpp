#include <fcntl.h>
#include <unistd.h>
 
#include <iostream>
#include <string>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
 
#include "caffe.pb.h"
using namespace caffe;
using namespace std;
 
using google::protobuf::io::FileInputStream;
using google::protobuf::Message;
bool ReadProtoFromTextFile(const char* filename, Message* proto) {
  int fd = open(filename, O_RDONLY);
  FileInputStream* input = new FileInputStream(fd);
  bool success = google::protobuf::TextFormat::Parse(input, proto);
  delete input;
  close(fd);
  return success;
}
 
 
int main()
{
    SolverParameter SGD;
 
    if(!ReadProtoFromTextFile("solver.prototxt", &SGD))
    {
       cout<<"error opening file"<<endl; 
       return -1;
    }
 
    cout<<"hello,world"<<endl;
    cout<<SGD.train_net()<<endl;
    cout<<SGD.base_lr()<<endl;
    cout<<SGD.lr_policy()<<endl;
 
    NetParameter VGG16;
    if(!ReadProtoFromTextFile("train.prototxt", &VGG16))
    {
       cout<<"error opening file"<<endl; 
       return -1;
    }
    cout<<VGG16.name()<<endl;
    return 0;
}
