#ifndef __Rt_PROCESSMANAGER_HH
#define __Rt_PROCESSMANAGER_HH

#include <ostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

class ProcessManager 
{
  int n_pids, n_live;
  pid_t *pids;

public:
  pid_t child_pid;
  int verbose;

  ProcessManager(int _n_pids)
  : n_pids(_n_pids), n_live(0), verbose(0)
  {
    pids = new pid_t[n_pids];
    child_pid = 0;
  }
  ~ProcessManager()
  {
    delete [] pids;
  }

  const pid_t *begin() const { return pids; }
  const pid_t *end() const { return pids + n_pids; }

  int busy() { return n_live >= n_pids; }

  // Return true in child process.
  int fork()
  {
    pid_t pid;

    if ( n_pids <= 1 ) {
      // run fork() inline and disable exit().
      if ( verbose ) { std::cerr << "0"; std::cerr.flush(); }
      child_pid = 0;
      return 1;
    }

    do {
      if ( busy() ) wait();
      pid = ::fork();
      if ( pid < 0 ) {
        if ( verbose ) { std::cerr << "E"; std::cerr.flush(); }
        sleep(1);
      }
    } while ( pid < 0 );

    if ( pid > 0 ) {
      n_live ++;
      for ( int i = 0; i < n_pids; ++ i ) {
        if ( ! pids[i] ) {
          // std::cerr << "  pid forked " << pid << "\n";
          if ( verbose ) { std::cerr << "+"; std::cerr.flush(); }
          pids[i] = pid;
          break;
        }
      }
      child_pid = pid;
    } else {
      child_pid = getpid();
    }

    return ! pid;
  }

  int exit(int code)
  {
    if ( child_pid ) ::exit(code);
    return 0;
  }

  int check()
  {
    pid_t pid;

    for ( int i = 0; i < n_pids; ++ i ) {
      if ( (pid = pids[i]) ) {
        // std::cerr << "  checking pid " << pid << "\n";
        int status = 0;
        if ( waitpid(pid, &status, WNOHANG) > 0 ) { 
          // std::cerr << "  pid stopped " << pid << " status " << status << "\n";
          if ( verbose ) { std::cerr << "-"; std::cerr.flush(); }
          pids[i] = 0;
          n_live --;
          break;
        }
      }
    }
    return busy();
  }

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

  int join()
  {
    pid_t pid;

    for ( int i = 0; i < n_pids; ++ i ) {
      if ( (pid = pids[i]) ) {
        // std::cerr << "  pid wait " << pid << "\n";
        if ( verbose ) { std::cerr << "w"; std::cerr.flush(); }
        waitpid(pid, 0, 0);
        pids[i] = 0;
        -- n_live;
      }
    }
    return busy();
  }

  friend std::ostream& operator <<(std::ostream &os, const ProcessManager &pm) {
    os << "ProcessManager(" << pm.n_pids;
    for ( int i = 0; i < pm.n_pids; ++ i ) {
      os << ", " << pm.pids[i];
    }
    return os << "])";
  }
};

#endif
