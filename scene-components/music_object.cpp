#include "music_object.hpp"

MusicObject::MusicObject(const std::string& path) {
    if (!m_music.openFromFile(path)) {
        std::cerr << "Failed to load music file: " << path << std::endl;
    }
    else {
        m_music.setLoop(true);
    }
}
void MusicObject::play() {
    m_music.play();
}

void MusicObject::stop() {
    m_music.stop();
}

void MusicObject::pause() {
    m_music.pause();
}

void MusicObject::resume() {
    m_music.play();
}

void MusicObject::change_music(const std::string& new_path) {
    if (!m_music.openFromFile(new_path)) {
        std::cerr << "Failed to load music file: " << new_path << std::endl;
    }
    else {
        m_music.setLoop(true);
        m_music.play();
    }
}
