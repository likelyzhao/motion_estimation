#ifndef OD_SRC_COMMON_IO_HPP
#define OD_SRC_COMMON_IO_HPP

#include <google/protobuf/message.h>

namespace OD {

namespace IO {

using google::protobuf::Message;

bool ReadProtoFromBinaryFile(const std::string &proto_file, Message *proto);

bool ReadProtoFromArray(const void *proto_data, int proto_size,
                        google::protobuf::Message *proto);

}  // namespace IO

}  // namespace OD

#endif  // OD_SRC_COMMON_IO_HPP
