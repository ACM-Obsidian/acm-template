syntax on
syntax enable
set nu
set cin "自动缩进
color elflord
set ts=4
set sw=4

map<C-b> <esc>:w<cr>:!g++ -o %< % -Wall -g<cr>
map<C-f> <esc>:w<cr>:!./%<<cr>
map<f5> <esc>:w<cr>:!gdb %<<cr>
map<F7> <esc>:w<cr>:!g++ -o %< % -Wall -g -O2<cr>
