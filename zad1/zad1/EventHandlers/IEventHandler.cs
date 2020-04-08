using System;

namespace zad1.EventHandlers
{
    interface IEventHandler
    {
        void Handle(object sender, EventArgs e);
    }
}
