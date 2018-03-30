#ifndef EXECUTE_MANAGER_H
#define EXECUTE_MANAGER_H

#include "Job.hpp"
#include <map>
#include <mutex>
#include <string>
#include "Results.hpp"
#include "ProtoFiles/TaskMsg.pb.h"
#include <atomic>
#include <qthreadpool.h>

namespace manager
{
  class ExecuteManager
  {
  public:
    ExecuteManager(std::string m_database);
    ~ExecuteManager();

    void addJob(manager::Job job);
    void addTasks(msg::TaskMsg* pTask);
    void removeJob(int id);
    void modifyJob(int id, std::string field, std::string value);

  private:
    std::map<int, JobInfo> m_jobs;
    std::string m_database;
    std::atomic<int> m_size;
    std::shared_ptr<std::mutex> m_pResultsMutex;
    std::shared_ptr<std::vector<Result>> m_pResults;
    std::shared_ptr<QThreadPool> m_pThreadPool;
  };

} // namespace manager

#endif