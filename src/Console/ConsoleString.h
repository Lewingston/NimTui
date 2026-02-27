#pragma once

#include <string>

namespace TUI {

    class ConsoleString {

        public:

            ConsoleString() = delete;

            virtual ~ConsoleString() = delete;

            [[nodiscard]] static std::string getSubstring(const std::string& str,
                                                          std::size_t pos,
                                                          std::size_t count);

            [[nodiscard]] static std::size_t getByteCountForConsoleSize(const std::string& str,
                                                                        std::size_t size);

        private:
    };
}
