# Environment Variables & Export
set PROJECT_ROOT .
# Binary support
set PATH $PROJECT_ROOT/tool-bin:$PATH
set ECE551PATH $PATH
set AUTHOR THZHANG
export PROJECT_ROOT
set TEST_ROOT $PROJECT_ROOT/test
export TEST_ROOT
set DESKTOP_SESSION ece551

# Aliases
alias cdhome=cd $PROJECT_ROOT
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

alias env=export

# Numeric support
alias caffe0_test=caffe0 <$PROJECT_ROOT/test/numeric_test.txt

# Test preparation
cd $PROJECT_ROOT

# Please do not edit the lines above! If you would like to add more configurations, add them below.
