git 使用：
git config --global user.name "用户名"
git config --global user.email "邮箱地址"

<!-- 设置ssh key -->
git init
<!-- ssh-keygen -t rsa -C "邮箱地址"
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
chmod 600 ~/.ssh/authorized_keys
ssh -T git@github.com -->

<!-- 本地项目与远程仓库建立关联 -->
git remote add origin git@github.com:username/repo.git
git add ./
git pull origin dev
git commit -m "WHAT"
git push origin dev


<!-- git config --global core.editor "vim"
git config --global core.pager "less -R"
git config --global color.ui auto
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.ci commit -->