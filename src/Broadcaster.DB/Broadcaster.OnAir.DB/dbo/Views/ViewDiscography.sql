
CREATE VIEW [dbo].[ViewDiscography]
AS
SELECT Broadcaster.dbo.MusicTracks.ID, 
    Broadcaster.dbo.MusicTracks.ArtistID, 
    Broadcaster.dbo.MusicTracks.Title, 
    Broadcaster.dbo.Artists.Name AS Artist
FROM Broadcaster.dbo.MusicTracks INNER JOIN
    Broadcaster.dbo.Artists ON 
    Broadcaster.dbo.MusicTracks.ArtistID = Broadcaster.dbo.Artists.ID
WHERE (Broadcaster.dbo.MusicTracks.Activ = 1)

