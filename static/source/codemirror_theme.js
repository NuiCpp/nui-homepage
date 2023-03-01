import { EditorView } from '@codemirror/view'
import { HighlightStyle, syntaxHighlighting } from '@codemirror/language'
import { tags } from '@lezer/highlight'

const bgBase = '#303030',
    fgBase = '#DDDDDD',
    bgHighlight = '#B9D2FF',
    gray = '#b0b0b0',
    lightGray = '#e0e0e0',
    darkGray = '#808080',
    black = '#000000'

const invalid = '#fc6d24',
    darkBackground = '#292d30',
    highlightBackground = bgHighlight + '30',
    background = bgBase,
    tooltipBackground = fgBase,
    selection = '#202325',
    cursor = fgBase

/// The editor theme styles for Basic Dark.
export const darkTheme = EditorView.theme(
    {
        '&': {
            color: fgBase,
            backgroundColor: background
        },

        '.cm-content': {
            caretColor: cursor
        },

        '.cm-cursor, .cm-dropCursor': { borderLeftColor: cursor },
        '&.cm-focused .cm-selectionBackground, .cm-selectionBackground, .cm-content ::selection':
            { backgroundColor: selection },

        '.cm-panels': { backgroundColor: darkBackground, color: gray },
        '.cm-panels.cm-panels-top': { borderBottom: '2px solid black' },
        '.cm-panels.cm-panels-bottom': { borderTop: '2px solid black' },

        '.cm-searchMatch': {
            backgroundColor: bgHighlight,
            outline: `1px solid ${gray}`,
            color: black
        },
        '.cm-searchMatch.cm-searchMatch-selected': {
            backgroundColor: lightGray,
            color: black
        },

        '.cm-activeLine': { backgroundColor: highlightBackground },
        '.cm-selectionMatch': { backgroundColor: highlightBackground },

        '&.cm-focused .cm-matchingBracket, &.cm-focused .cm-nonmatchingBracket': {
            outline: `1px solid ${gray}`
        },

        '&.cm-focused .cm-matchingBracket': {
            backgroundColor: bgHighlight,
            color: black
        },

        '.cm-gutters': {
            borderRight: `1px solid #ffffff10`,
            color: darkGray,
            backgroundColor: darkBackground
        },

        '.cm-activeLineGutter': {
            backgroundColor: highlightBackground
        },

        '.cm-foldPlaceholder': {
            backgroundColor: 'transparent',
            border: 'none',
            color: bgHighlight
        },

        '.cm-tooltip': {
            border: 'none',
            backgroundColor: tooltipBackground
        },
        '.cm-tooltip .cm-tooltip-arrow:before': {
            borderTopColor: 'transparent',
            borderBottomColor: 'transparent'
        },
        '.cm-tooltip .cm-tooltip-arrow:after': {
            borderTopColor: tooltipBackground,
            borderBottomColor: tooltipBackground
        },
        '.cm-tooltip-autocomplete': {
            '& > ul > li[aria-selected]': {
                backgroundColor: highlightBackground,
                color: gray
            }
        }
    },
    { dark: true }
)

const blueish = '#337DFF';
const yellowish = '#FFD700';
const classColor = '#6DFFC8';
const stringLiteralColor = '#EE5A5A';
const magenta = '#d33682';

/// The highlighting style for code in the Basic Light theme.
export const darkHighlightStyle = HighlightStyle.define([
    { tag: tags.keyword, color: "#fc6" },
    { tag: [tags.function(tags.variableName)], color: blueish },
    {
        tag: [tags.color, tags.constant(tags.name), tags.standard(tags.name)],
        color: yellowish
    },
    {
        tag: [tags.typeName, tags.className],
        color: classColor
    },
    { tag: [tags.string], color: stringLiteralColor },
    { tag: [tags.comment], color: '#FF8539', fontStyle: 'italic' },
    {
        tag: [tags.namespace, tags.macroName, tags.annotation],
        color: magenta
    }
])

/// Extension to enable the Basic Dark theme (both the editor theme and
/// the highlight style).
export const dark = [
    darkTheme,
    syntaxHighlighting(darkHighlightStyle),
]