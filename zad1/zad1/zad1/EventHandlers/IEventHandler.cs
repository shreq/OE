using System;
using System.Collections.Generic;
using System.Text;

namespace zad1.EventHandlers
{
    interface IEventHandler
    {
        void Handle(object sender, EventArgs e);
    }
}
