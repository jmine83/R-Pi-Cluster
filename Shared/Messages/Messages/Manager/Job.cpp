#include "Job.hpp"
#include <fstream>
#include <iostream>

manager::Job::Job()
  : m_myId(-1),
  m_priority(-1),
  m_taskPerBundle(-1),
  m_gitUrl(""),
  m_taskManager(-1, -1),
  m_resultManager(-1),
  m_database(""),
  m_name(),
  m_toExec(),
  m_status(manager::Status::PLAY)
{}


manager::Job::Job(int id,
                  int size,
                  int pri,
                  int taskpb,
                  std::string gitUrl,
                  std::string database,
                  std::string cloneScript)
  : m_myId(id),
    m_priority(pri),
    m_taskPerBundle(taskpb),
    m_gitUrl(gitUrl),
    m_taskManager(id, size),
    m_resultManager(id),
    m_database(database),
    m_name(),
    m_toExec(),
    m_status(manager::Status::PLAY)
{
  m_name = gitUrl;
  int spot;
  while ((spot = m_name.find("/")) != std::string::npos)
  {
    m_name.erase(0, spot + 1);
  }
  m_name.erase(m_name.size() - 4);
  system(std::string("dir").c_str());
  system(std::string(cloneScript + " " + m_name + " " + m_gitUrl).c_str());
  m_taskManager.populateFields("Jobs/" + m_name + "/TaskLists.txt");
  system(std::string("mkdir " + m_database + std::to_string(m_myId)).c_str());
  std::ifstream fin("Jobs/" + m_name + "/" + m_name + "/Exec.txt");
  std::getline(fin, m_toExec);
}

manager::Job::~Job()
{
  // can remove folder
}

void manager::Job::addResults(std::vector<manager::Result> results)
{
  m_resultManager.addResult(results);
}

std::vector<manager::Task> manager::Job::getTasks(int amount)
{
  return m_taskManager.getNextTasks(amount);
}

int manager::Job::getJobId()
{
  return m_myId;
}

manager::Status manager::Job::getStatus()
{
  return m_status;
}
void manager::Job::setStatus(manager::Status s)
{
  m_status = s;
}

std::string manager::Job::getName()
{
  return m_name;
}

std::string manager::Job::getExec()
{
  return m_toExec;
}

int manager::Job::getPriority()
{
  return m_priority;
}

void manager::Job::setPriority(int priority)
{
  m_priority = priority;
}


int manager::Job::getTasksPerBundle()
{
  return m_taskPerBundle;
}

void manager::Job::setTasksPerBundle(int bundle)
{
  m_taskPerBundle = bundle;
}
