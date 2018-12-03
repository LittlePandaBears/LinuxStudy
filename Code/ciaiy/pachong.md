# selenium简单爬虫爬取果壳谣言粉碎机

## selenium介绍

> selenium, 是一个用于Web应用程序测试的工具。Selenium测试直接运行在浏览器中，就像真正的用户在操作一样。
> 框架底层使用JavaScript模拟真实用户对浏览器进行操作。测试脚本执行时，浏览器自动按照脚本代码做出点击，输入，打开，验证等操作，就像真实用户所做的一样，从终端用户的角度测试应用程序。
>
> 来源： 百度百科

---

## 思路

我们可以使用selenium来模拟用户对网站进行浏览， 然后爬取其数据

步骤：

- 果壳网为了减少服务器的性能开销而使用了懒加载手段，因此我们需要模拟鼠标滚轮进行滚动以获取更多的文章链接

- 通过阅读网页源码， 获取文章标题以及链接

- 通过阅读文章网页源码， 获取所需信息

---

## 利用到的函数

- selenium get_attribute()

    我们可以使用这个函数来获取标签元素的内容
    |||
    |:-:|:-:|
    |'textContent'|获取内容|
    |'innerHTML'|获取元素内所有HTML|
    |'outerHTML'|获取选中元素的HTML|
- browser.find_element_by_*()

    我们可以使用这个函数来定位标签元素
    |||
    |:-:|:-:|
    |by_id|可以通过html里的id定位|
    |by_css_selector|可以通过类选择器来定位|
##　分析网页源代码

### 谣言粉碎机首页源代码

**``截取部分代码``**

``` HTML
<a class="article-title" href="https://www.guokr.com/article/442723/" target="_blank"
data-gaevent="scientific_title:v1.1.1.1:scientific">为什么会有“两头春”和“无春年”？</a>
```

我们可以看出，当我们选取``article-title``元素时，我们可以使用``item.get_attribute('href')``来获取每个文章的链接

### 文章网页源代码

**``截取部分代码``**

``` HTML
<h1 itemprop="http://purl.org/dc/terms/title" id="articleTitle">淡水虹鳟终于成功打入海水三文鱼团体？会对我们有啥影响？</h1>
```

由以上代码可知， 当我们选取``articleTitle``元素时， 我们可以使用``get_attribute('innerHTML')``来获取文章标题

``` HTML
<div class="document">
    <p hidden="">本文作者:吃货研究所</p>
    <div>
        <p>8月11日，青海省人民政府网站发布一条消息：《生食三文鱼》团体标准发布。</p>
        <p>中国水产流通与加工协会会同三文鱼分会成员单位青海民泽龙羊峡生态水殖有限公司、上海荷裕冷冻食品有限公等十家单位共同起草的《生食三文鱼》标准正式发布。</p>
    </div>
    ...
</div>

```

正文部分的代码量很大， 但是我们只需要找到``document``元素， 选取之后， 我们使用``get_attribute('textContent')``来获取文章正文

## 总结

使用爬虫来爬取文章， 需要对html以及CSS有一定的了解...