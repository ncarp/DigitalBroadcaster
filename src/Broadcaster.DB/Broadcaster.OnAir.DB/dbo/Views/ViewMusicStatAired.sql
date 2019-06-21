CREATE VIEW [dbo].[ViewMusicStatAired]
AS
SELECT     Broadcaster.dbo.MusicTracks.ID, Broadcaster.dbo.MusicTracks.ArtistID, Broadcaster.dbo.MusicTracks.LanguageID, Broadcaster.dbo.MusicTracks.CategoryID, 
                      Broadcaster.dbo.Artists.Name AS ArtistName, Broadcaster.dbo.MusicTracks.Title, Broadcaster.dbo.Languages.Name AS Language, 
                      Broadcaster.dbo.Categories.Name AS Category, dbo.OnAirLog.[Date]
FROM         Broadcaster.dbo.MusicTracks INNER JOIN
                      dbo.OnAirLog ON Broadcaster.dbo.MusicTracks.ID = dbo.OnAirLog.ItemID INNER JOIN
                      Broadcaster.dbo.Languages ON Broadcaster.dbo.MusicTracks.LanguageID = Broadcaster.dbo.Languages.ID INNER JOIN
                      Broadcaster.dbo.Artists ON Broadcaster.dbo.MusicTracks.ArtistID = Broadcaster.dbo.Artists.ID INNER JOIN
                      Broadcaster.dbo.Categories ON Broadcaster.dbo.MusicTracks.CategoryID = Broadcaster.dbo.Categories.ID
WHERE     (dbo.OnAirLog.ItemType = 51)
