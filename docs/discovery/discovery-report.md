# Discovery report

## Problem statement

An animation studio needs a ray tracer that its own developers can extend and maintain for years, because it spends 2 million on licences for renderers it cannot change, but the code must outlive the people who wrote it.

## Client interview summary

I asked one question, marked "me". The others came from classmates. I noted the answers during the interview; the wording of the classmates' questions is rebuilt from my notes.

### Scope: render images

**Need:** Software that takes scene files and renders images. Nothing more.

> **Q (a classmate):** "What is the main purpose of the software?"
>
> **A:** "The main purpose is to render images." "Just want to render."

> **Q (a classmate):** "Do you need a user interface?"
>
> **A:** "Don't need an interface."

> **Q (a classmate):** "How will the designers give their scenes to the ray tracer?"
>
> **A:** The designers set up the scene in third-party software. The files are then given to our software.

> **Q (a classmate):** "What kind of films do you make?"
>
> **A:** "Mainly full animation, like Toy Story."

> **Q (me):** "What are the most important surfaces to cover in the renderer?"
>
> **A:** Diffuse shaders, reflection and shadows.

**My conclusion:** No interface to build. The ray tracer reads a scene file and writes an image. The first version must handle matte surfaces, reflections and shadows.

### Speed and scale

**Need:** Render a whole film in two months at most.

> **Q (a classmate):** "How long is the film, and how long can the rendering take?"
>
> **A:** 90 minutes, 24 frames per second, HD. Once the creators are done, no more than two months of rendering.

> **Q (a classmate):** "On how many machines, and how many renders per image?"
>
> **A:** 100 machines. About ten renders per image in an average workflow.

> **Q (a classmate):** "What matters more for the designers, speed or quality?"
>
> **A:** The designers do not want to wait too long to see a render, but "the main thing is high quality image".

**My conclusion:** The film is 129,600 frames (90 × 60 × 24). With 100 machines for 60 days and ten renders per frame, one render can take about 6 to 7 minutes on one machine. This is my own calculation, not a number from the client.

### Extending and maintaining

**Need:** The studio's developers add their own features and maintain the code for years, without us.

> **Q (a classmate):** "What is the most important thing for you?"
>
> **A:** "Main thing is to be able to add their own feature."

> **Q (a classmate):** "Who will maintain the software?"
>
> **A:** "We would like to maintain it in the long term." "We do have a dev team."

> **Q (a classmate):** "Is there something we forgot to ask?"
>
> **A:** "What happens when someone leaves the team? We need to maintain it without you."

> **Q (a classmate):** "Do you have rules for the code, or a format for the documentation?"
>
> **A:** No specific rules for the code. No specific format for the documentation.

**My conclusion:** The code must be understood by people who did not write it. The client gives no rules, so I have to choose them and document them.

### Open source and partners

**Need:** All the code is open source, and partner studios use the software too.

> **Q (a classmate):** "Will all the code be open source?"
>
> **A:** "All open source."

> **Q (a classmate):** "Who else will use the software?"
>
> **A:** "We do rely on partners to do the rendering, so they will use the software."

### Cost

**Need:** Own the product and stop paying for licences.

> **Q (a classmate):** "Why not keep using an existing renderer?"
>
> **A:** "2 million in licences, so we need an internal product."

> **Q (a classmate):** "What is your budget?"
>
> **A:** 500,000 euros at most.

### Proof that it works

**Need:** When an image is wrong, the studio can find out why and fix it.

> **Q (a classmate):** "What would show that the ray tracer covers your need?"
>
> **A:** I did not hear the first point. The second was: if there is a problem in an image, they need to know why and be able to correct it.

### Open questions

- Must everything be rendered on the CPU? I noted this with a question mark.
- Contradiction: the designers want fast previews, but quality comes first.

## State of the art

Prices checked on 16 November 2026. Capabilities use the same two criteria: rendering on many machines, and whether the studio can change the code. "Not checked" means I did not find it on the cited page.

| Solution  | Maker                                            | Licence                                                | Pricing (date checked)                                                                        | Capabilities                                                           | Sources                                                                                          |
| --------- | ------------------------------------------------ | ------------------------------------------------------ | --------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------ |
| RenderMan | Pixar                                            | Commercial, closed source. | $595 per licence, plus $250 per year for maintenance (16 Nov 2026)                            | Many machines: yes, with Tractor (included). Code: closed | [renderman.pixar.com/store](https://renderman.pixar.com/store)                                   |
| V-Ray     | Chaos                                            | Commercial, closed source, subscription                | Solo: €39.50 per month, billed yearly. Premium: €58.90 per month, billed yearly (16 Nov 2026) | Many machines: not checked. Code: closed                          | [chaos.com/vray/buy-online](https://www.chaos.com/vray/buy-online)                               |
| Cycles    | Blender project                                  | Open source, Apache 2.0                                | Free (16 Nov 2026)                                                                            | Many machines: not checked. Code: open                   | [cycles-renderer.org](https://www.cycles-renderer.org/)                                          |
| MoonRay   | DreamWorks Animation                             | Open source, Apache 2.0                                | Free (16 Nov 2026)                                                                            | Many machines: yes, with Arras (included). Code: open     | [github.com/dreamworksanimation/openmoonray](https://github.com/dreamworksanimation/openmoonray) |
| pbrt-v4   | Authors of the book _Physically Based Rendering_ | Open source, Apache 2.0                                | Free (16 Nov 2026)                                                                            | Many machines: not checked. Code: open, explained in the book      | [github.com/mmp/pbrt-v4](https://github.com/mmp/pbrt-v4)                                         |

All of these rendering engines produce cinematic-quality images, and three of them are free. The client spends 2 million on licences even though free engines exist. The commercial engines are closed, so the studio cannot add its own features. The free engines were developed for a third party, so they are difficult to maintain for a team that did not develop them. What the client lacks is a ray tracing engine that its own developers can understand, extend and keep running even when employees leave the company.

## What is ray tracing?

A ray tracer takes a scene as input: objects, their materials, lights and a camera. It then outputs an image, which is a grid of pixels of different colours. For each pixel, it projects a ray toward the scene and identifies the nearest object hit by that ray. It calculates the colour at that location based on the material and the lights. To detect shadows, it sends a ray toward each light source: if something blocks it, the point is in shadow. If the surface is shiny, the ray bounces off it like a ball, and the process repeats along the new ray, up to a maximum number of bounces.

**Sources:** I started from [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) (Shirley, Black, Hollasch). The reference I would come back to is [Physically Based Rendering](https://pbr-book.org/4ed/Introduction), free online.

## What is C++?

### Programming paradigms

C++ supports functions, object-oriented programming (classes), generic programming (templates) and a bit of functional programming. I know JavaScript, TypeScript and Python. They also mix several styles, for example functions and classes. JavaScript and Python are dynamically typed languages. TypeScript performs type checks, just like C++.

C++ is compiled into machine code. This has two advantages: many errors are detected before the program runs, and execution is fast.

### What to watch out for

- **Memory:** there is no garbage collector. Traps: using an object that has already been destroyed, or never freeing it.
- **Copies:** by default, an object is copied when passed to a function. In JavaScript and Python it is shared. I must choose between a copy and a reference.
- **Undefined behaviour:** reading outside an array or using a variable with no value does not cause an error. The program just gives a wrong result.
- **Compilation:** header files, source files and a build step.

### Shaping the domain model

- One class per concept of the client's domain, with the client's word: ray, scene, camera, light, material.
- Small values such as vectors and colours are simple types, copied and never modified.
- Things that come in several kinds, such as shapes, share a common interface. A new shape can be added without changing the renderer.
- Ownership is clear: for example, the scene owns its objects.

**Sources:** I started from [learncpp.com](https://www.learncpp.com/). The reference I would come back to is the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) (Stroustrup, Sutter).
