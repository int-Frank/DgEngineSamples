
#include <thread>

#include "Engine.h"

#include "common.h"

class Game : public DgE::Application
{
public:
  Game(Opts const & a_opts)
    : Application(a_opts)
  {
    uint32_t threadCount = std::thread::hardware_concurrency();
    if (threadCount < 3)
      threadCount = 1;
    else
      threadCount -= 2;

    InitWorkerPool(threadCount);
  }

  ~Game()
  {
    DestroyWorkerPool();
  }

};

DgE::Application* DgE::CreateApplication()
{
  Application::Opts opts;
  return new Game(opts);
}
