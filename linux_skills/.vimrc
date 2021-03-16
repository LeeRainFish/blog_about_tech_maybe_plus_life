" set number line
set nu
" 设置缩进
set shiftwidth=4
set tabstop=4
set ts=4
set expandtab
set autoindent 
autocmd FileType make set noexpandtab
filetype plugin indent on

" 插入模式下jk映射为esc
imap jk <Esc>

set autowrite

" vim-plug
" nerdtree
"
call plug#begin()
Plug 'preservim/nerdtree'
call plug#end()
autocmd StdinReadPre * let s:std_in=1
autocmd VimEnter * if argc() == 0 && !exists("s:std_in") | NERDTree | endif

