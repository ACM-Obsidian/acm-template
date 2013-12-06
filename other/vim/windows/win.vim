syntax on
syntax enable
set nowrap "取消折行
set nu
set cin "自动缩进
color koehler
set ts=4 "设置tab和缩进长度
set sw=4

map<C-b> <esc>:w<cr>:!g++ -o %< % -Wall -g<cr>
map<C-f> <esc>:w<cr>:!%<<cr>
map<f5> <esc>:w<cr>:!gdb %<<cr>
map<F7> <esc>:w<cr>:!g++ -o %< % -Wall -g -O2<cr>

set nohlsearch "取消搜索高亮
set nocompatible "去掉兼容vi的模式
set backspace=indent,eol,start "解决退格键问题，可选:w
