# yhW 的个人博客

基于 [Astro](https://astro.build/) 与 [Fuwari](https://github.com/saicaca/fuwari) 构建，使用 GitHub Actions 发布到 GitHub Pages。

- 网站：<https://yhuwa.com>
- GitHub：<https://github.com/Wyh111625>
- 部署仓库：<https://github.com/Wyh111625/Wyh111625.github.io>

## 本地开发

需要 Node.js 22 和 pnpm 9。

```bash
corepack enable
pnpm install
pnpm dev
```

访问 <http://localhost:4321>。

## 常用命令

```bash
pnpm dev                 # 启动开发服务器
pnpm build               # 构建生产版本到 dist/
pnpm preview             # 预览生产构建
pnpm check               # Astro 类型与内容检查
pnpm new-post <filename> # 新建文章
pnpm format              # 格式化 src/
```

## 写文章

文章位于 `src/content/posts/`，示例 Front Matter：

```yaml
---
title: 文章标题
published: 2026-09-05
description: 文章摘要
tags: [Astro, Fuwari]
category: 技术
draft: false
---
```

## 站点配置

- `src/config.ts`：标题、语言、主题颜色、导航和个人信息
- `astro.config.mjs`：站点域名及 Astro 配置
- `src/content/spec/about.md`：关于页面
- `public/CNAME`：GitHub Pages 自定义域名
- `.github/workflows/pages.yml`：自动构建和部署

每次推送到 `main` 分支都会自动部署。迁移前的 Hexo + Butterfly 版本保存在远程分支 `backup/hexo-butterfly`。
