
local mingw = 'C:\\msys64\\msys2_shell.cmd -defterm -no-start -mingw64 -here -lc'
local buildDemo = 'cmake --build ./build --target ImTuiDemo'
local buildTest = 'cmake --build ./build --target ImTuiTest'

function runInConsole(command)

    vim.cmd('split')
    vim.cmd("wa")
    vim.cmd('term ' .. command)
    vim.api.nvim_input("G")
end

function runInMingw(command)

    runInConsole(mingw .. ' "' .. command .. '"')
end

-- Build demo
vim.keymap.set("n", "<C-b>", function()

    runInMingw(buildDemo)

end)

-- Build tests
vim.keymap.set("n", "<C-t>", function()

    runInMingw(buildTest)

end)

-- Run Demo
vim.keymap.set("n", "<F5>", function()

    runInMingw(buildDemo .. ' && ./build/demo/ImTuiDemo.exe')

end)

-- Run Tests
vim.keymap.set("n", "<F6>", function()

    runInMingw(buildTest .. ' && ctest --test-dir build/test')

end)

-- Rerun failed test
vim.keymap.set("n", "<F7>", function()

    runInMingw(buildTest .. ' && ctest --test-dir build/test --rerun-failed --output-on-failure')

end)

-- Generate coverage report
vim.keymap.set("n", "<F8>", function()

    local createCoverageReport = 'cmake --build ./build --target coverage'
    local openReport = 'explorer build\\coverage\\coverage.html'

    runInConsole(mingw .. ' "' .. buildTest .. ' && ' .. createCoverageReport .. '" && ' .. openReport)

end)
