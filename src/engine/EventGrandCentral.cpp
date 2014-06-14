#include "EventGrandCentral.hpp"

void Topaz::Engine::EventGrandCentral::addListener(Listener *listener)
{
  _listeners.push_back(listener);
}

void Topaz::Engine::EventGrandCentral::notify(Event event)
{
  for (int i = 0; i < _listeners.size(); ++i)
  {
    _listeners[i]->handleEvent(event);
  }
}
