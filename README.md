# Hexo Butterfly 个人博客

这是一个可直接发布到 GitHub Pages 的个人博客，基于 Hexo 8 与 Butterfly 5 搭建。

## 本地运行

需要 Node.js 22 或更新版本。

```bash
npm install
npm run server
```

浏览器访问 <http://localhost:4000>。修改内容后如遇缓存问题，执行：

```bash
npm run clean
npm run build
```

## 当前站点信息

- 博客名称：`yhW的个人博客`
- 作者：`WYH`
- GitHub：`Wyh111625`
- 自定义域名：`yhuwa.com`

可以用自己的 SVG、PNG 或 WebP 文件替换 `source/img/avatar.svg` 和 `source/img/favicon.svg`。

## 写文章

新建文章：

```bash
npm run new -- "文章标题"
```

文件会生成在 `source/_posts/`。常用 Front Matter：

```yaml
---
title: 文章标题
date: 2026-09-04 10:00:00
categories:
  - 技术
tags:
  - Hexo
description: 显示在首页和搜索结果里的摘要
---
```

## 发布到 GitHub Pages

在 GitHub 新建一个名为 `Wyh111625.github.io` 的公开空仓库，然后在本目录运行：

```bash
git init
git add .
git commit -m "Initialize Hexo Butterfly blog"
git branch -M main
git remote add origin https://github.com/Wyh111625/Wyh111625.github.io.git
git push -u origin main
```

进入仓库的 **Settings → Pages**，将 **Source** 设为 **GitHub Actions**。以后每次推送 `main` 分支，`.github/workflows/pages.yml` 都会自动构建并发布网站。

如果暂时不用自定义域名，而仓库名又不是 `USERNAME.github.io`，需要把 `_config.yml` 改为：

```yaml
url: https://USERNAME.github.io/REPOSITORY
root: /REPOSITORY/
```

使用自定义域名时，保持 `root: /`。

## 绑定自定义域名

1. 项目已生成 `source/CNAME`，内容为 `yhuwa.com`。
2. 在 GitHub 仓库 **Settings → Pages → Custom domain** 填写 `yhuwa.com`。
3. 在域名服务商为根域名 `@` 添加四条 `A` 记录，分别指向 `185.199.108.153`、`185.199.109.153`、`185.199.110.153`、`185.199.111.153`。
4. 如需同时支持 `www.yhuwa.com`，为 `www` 添加一条 `CNAME`，指向 `Wyh111625.github.io`。

5. DNS 生效后，在 GitHub Pages 设置中启用 **Enforce HTTPS**。

## 开启 Giscus 评论（可选）

先在仓库启用 Discussions，并前往 <https://giscus.app/zh-CN> 生成配置。然后编辑 `_config.butterfly.yml`：

```yaml
comments:
  use: Giscus

giscus:
  repo: Wyh111625/Wyh111625.github.io
  repo_id: 生成的 repo ID
  category_id: 生成的 category ID
  light_theme: light
  dark_theme: dark
```

## 主要目录

```text
source/_posts/          博客文章
source/about/           关于页面
source/css/custom.css   自定义样式
_config.yml             Hexo 站点配置
_config.butterfly.yml   Butterfly 主题配置
.github/workflows/      GitHub Pages 自动部署
```

主题文档：<https://butterfly.js.org/>
