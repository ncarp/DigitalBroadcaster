CREATE VIEW [dbo].[ViewLogMusic]
AS
SELECT     dbo.[Log].[Date], dbo.Computers.Name AS Computer, dbo.SystemUsers.Name AS [User], dbo.Actions.[Action], dbo.ElementType.Name AS Type, 
                      RTRIM(dbo.Artists.Name) + ' - ' + RTRIM(dbo.MusicTracks.Title) AS Name
FROM         dbo.[Log] INNER JOIN
                      dbo.ElementType ON dbo.[Log].TypeID = dbo.ElementType.ID INNER JOIN
                      dbo.MusicTracks ON dbo.[Log].ItemID = dbo.MusicTracks.ID INNER JOIN
                      dbo.Artists ON dbo.MusicTracks.ArtistID = dbo.Artists.ID LEFT OUTER JOIN
                      dbo.Actions ON dbo.[Log].ActionID = dbo.Actions.ID LEFT OUTER JOIN
                      dbo.SystemUsers ON dbo.[Log].UserID = dbo.SystemUsers.Id LEFT OUTER JOIN
                      dbo.Computers ON dbo.[Log].ComputerID = dbo.Computers.ID
WHERE     (dbo.[Log].TypeID = 51)


