CREATE VIEW [dbo].[ViewLog]
AS
SELECT     dbo.ViewLogMusic.*
FROM         dbo.ViewLogMusic
UNION
SELECT     dbo.ViewLogJingles.*
FROM         dbo.viewlogJingles
UNION
SELECT     *
FROM         ViewLogSpots
