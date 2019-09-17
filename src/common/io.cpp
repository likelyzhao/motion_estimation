#include "io.hpp"
#include "log.hpp"

#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#elif defined(_WIN32)
#include <io.h>
#endif
#include <fcntl.h>
#include <fstream>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#if defined(SUPPORT_JSON)
#include <google/protobuf/util/json_util.h>
#endif

namespace OD {

namespace IO {

using google::protobuf::io::ArrayInputStream;
using google::protobuf::io::CodedInputStream;
using google::protobuf::io::FileInputStream;

bool ReadProtoFromBinaryFile(const std::string& proto_file, Message* proto) {
#if defined(_WIN32)
  int fd = open(proto_file.c_str(), O_RDONLY | O_BINARY);
#else
  int fd = open(proto_file.c_str(), O_RDONLY);
#endif
  CHECK_NE(fd, -1) << "File not found: " << proto_file;
  auto* raw_input = new FileInputStream(fd);
  auto* coded_input = new CodedInputStream(raw_input);
  coded_input->SetTotalBytesLimit(INT_MAX, 536870912);
  bool success = proto->ParseFromCodedStream(coded_input);
  delete coded_input;
  delete raw_input;
  close(fd);
  return success;
}

bool ReadProtoFromArray(const void* proto_data, int proto_size,
                        google::protobuf::Message* proto) {
  auto* param_array_input = new ArrayInputStream(proto_data, proto_size);
  auto* param_coded_input = new CodedInputStream(param_array_input);
  param_coded_input->SetTotalBytesLimit(INT_MAX, 1073741824);
  bool success = proto->ParseFromCodedStream(param_coded_input) &&
                 param_coded_input->ConsumedEntireMessage();
  delete param_coded_input;
  delete param_array_input;
  return success;
}

}  // namespace IO

}  // namespace Scope
