#ifndef EVENT_LISTENER_HPP
#define EVENT_LISTENER_HPP

#include <vector>
#include <iostream>

namespace Topaz {
  namespace Engine {
    struct Event {
      char* type;
    };

    class Listener {
    public:
      virtual void handleEvent(Event event) = 0;
    };

    class EventGrandCentral {
    public:
      static EventGrandCentral& instance() {
        static EventGrandCentral grandCentral;
        return grandCentral;
      }

      void addListener(Listener *listener);
      void notify(Event event);

    private:
      EventGrandCentral() {};
      std::vector<Listener*> _listeners;
    };

  }
}


#endif
