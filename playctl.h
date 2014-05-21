#ifndef PLAYCTL_H

#define PLAYCTL_H

namespace Slideshow {
    class PlayControl {
        private:
            class Private;
            Private *priv;
        protected:
        public:
            ~PlayControl();
            PlayControl(const char *file_plugin, const char *file, int w, int h);
            void play();
    };
}

#endif
