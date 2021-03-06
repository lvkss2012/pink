#include "bada_thread.h"
#include "xdebug.h"

#include "pb_conn.h"
#include <functional>
#include <string>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

using namespace pink;

BadaConn::BadaConn(int fd, ::std::string ip_port, Thread *thread) :
  PbConn(fd, ip_port)
{
  bada_thread_ = reinterpret_cast<BadaThread *>(thread);
}

BadaConn::~BadaConn()
{
  bada_thread_ = NULL;
}

int BadaConn::DealMessage()
{
  set_is_reply(true);
  log_info("In the badaconn DealMessage branch");
  ping_.ParseFromArray(rbuf_ + 4, header_len_);
  /*
   *   std::cout<<"Message is "<< ping_.DebugString();
   * 
   *   printf("%d %s %d\n", ping_.t(), ping_.address().data(), ping_.port());
   * 
   *   log_info("Bada Deal Message");
   */

  pingRes_.set_res(11234);
  pingRes_.set_mess("heiheidfdfdf");

  res_ = &pingRes_;

  int wbuf_len_ = res_->ByteSize();

  return 0;
}



BadaThread::BadaThread(int cron_interval):
  WorkerThread::WorkerThread(cron_interval) {
  bada_num_ = 10;
}

int BadaThread::PrintNum() {
  log_info("BadaThread num %d", bada_num_);
  return 0;
}

BadaThread::~BadaThread() {

}
