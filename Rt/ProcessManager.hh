#ifndef __Rt_PROCESSMANAGER_HH
#define __Rt_PROCESSMANAGER_HH

#include <ostream>
#include <vector>

#include <stdlib.h> // exit()
#include <unistd.h> // fork()
#include <sys/types.h> // pid_t
#include <sys/wait.h> // wait*()

class ProcessManager 
{
  int n_pids, n_live;
  std::vector<pid_t> pids;

public:
  int in_child;
  int verbose;

  ProcessManager(int _n_pids)
    : n_pids(_n_pids), n_live(0), in_child(0), verbose(0) { }

  // Return true if all processes are live.
  int busy() const { return n_live >= n_pids; }

  // Return true in child process.
  int fork()
  {
    pid_t pid;

    if ( n_pids <= 1 ) {
      // run "fork" inline and disable exit().
      if ( verbose ) { std::cerr << "0"; std::cerr.flush(); }
      in_child = 0;
      return 1;
    }

    do {
      // If busy, wait for one process to complete.
      if ( busy() ) wait();
      pid = ::fork();
      if ( pid < 0 ) {
        if ( verbose ) { std::cerr << "E"; std::cerr.flush(); }
        sleep(1);
      }
    } while ( pid < 0 );

    if ( pid > 0 ) {
      n_live ++;
      pids.push_back(pid);
      in_child = 0;
    } else {
      in_child = 1;
    }

    return ! pid;
  }

  int exit(int code = 0)
  {
    if ( in_child ) ::exit(code);
    return 0;
  }

  // Check if any process has completed.
  int check()
  {
    for ( auto p = pids.begin(); p != pids.end(); ++ p ) {
      pid_t pid = *p;
      // std::cerr << "  checking pid " << pid << "\n";
      int status = 0;
      if ( waitpid(pid, &status, WNOHANG) > 0 ) {
        // std::cerr << "  pid stopped " << pid << " status " << status << "\n";
        if ( verbose ) { std::cerr << "-"; std::cerr.flush(); }
        pids.erase(p);
        n_live --;
        break;
      }
    }
    return busy();
  }

  // Wait until at least one process completed.
  int wait()
  {
    do {
      check();
      if ( ! busy() ) break;
      if ( verbose ) { std::cerr << "."; std::cerr.flush(); }
      sleep(1);
    } while ( 1 );
    return busy();
  }

  // Wait for all processes to complete.
  int join()
  {
    for ( auto p = pids.begin(); p != pids.end(); ++ p ) {
      pid_t pid = *p;
      // std::cerr << "  pid wait " << pid << "\n";
      if ( verbose ) { std::cerr << "w"; std::cerr.flush(); }
      waitpid(pid, 0, 0);
      pids.erase(p);
      -- n_live;
      p = pids.begin();
    }
    return busy();
  }

  void write(std::ostream &os) const
  {
    os << "ProcessManager(" << n_pids;
    for ( auto p = pids.begin(); p != pids.end(); ++ p ) {
      os << ", " << *p;
    }
    os << ")";
  }

  friend std::ostream& operator <<(std::ostream &os, const ProcessManager &pm) {
    pm.write(os);
    return os;
  }
};

#endif
